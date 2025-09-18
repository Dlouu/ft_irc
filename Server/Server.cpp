#include "Server.hpp"

/*
Faut qu'on test le try and catch s'il fonctionne
GetClientByFD
*/

Server			*Server::_instance;
std::string		Server::_name;
std::string		Server::_password;

std::vector<std::string> extractMessages(std::string& buffer) {
	std::vector<std::string> messages;
	size_t pos = 0;

	while ((pos = buffer.find("\r\n")) != std::string::npos) {
		messages.push_back(buffer.substr(0, pos + 2));
		buffer.erase(0, pos + 2);
	}
	return messages;
}

Server *Server::getInstance( void ) {
    if ( Server::_instance == NULL ) {
        Server::_instance = new Server();
    }
    return Server::_instance;
}

void	Server::destroyInstance( void ) {
	if (_instance)
		delete _instance;
	_instance = NULL;
	return;
}

Server::Server( void ) {}

void	Server::init(int port, std::string password) {

	_password = password;
	_socket = -1;
	_epoll = -1;
	_name = SERVER_NAME;
	g_replies = createReplies();

	time_t now;
	time(&now);
	std::string date = ctime(&now);
	datetime = date.substr(0, date.length() - 1);
	g_vars = fillPermanentVars();

	if ((_socket = socket(AF_INET, SOCK_STREAM, 6)) == -1)
		std::cerr << "Error during socket creation\n";
	if (fcntl(_socket, F_SETFL, O_NONBLOCK) == -1) {
		std::cerr << "Error: serverSocker: fnctl()\n";
		return;
	}

	_address.sin_family = AF_INET;
	_address.sin_port = htons(port);
	_address.sin_addr.s_addr = INADDR_ANY;

	if (bind(_socket, (struct sockaddr*)&_address, sizeof(_address))) {
		std::cerr << "Error: serverSocker: bind()\n";
		close(_socket);
		return;
	}

	if (listen(_socket, MAX_EVENTS)) {
		std::cerr << "Error: serverSocker: listen()\n";
		close(_socket);
		return;
	}

	_epoll = epoll_create1(0);
	if (_epoll < 0) {
		std::cerr << "Error: epoll_create1()\n";
		close(_socket);
		return;
	}

	_event.events = EPOLLIN;
	_event.data.fd = _socket;
	if (epoll_ctl(_epoll, EPOLL_CTL_ADD, _socket, &_event)) {
		std::cerr << "Error: first epoll_ctl()\n";
		close(_socket);
		return;
	}
}

Server::~Server() {
	if (_socket != -1)
		close(_socket);
	if (_epoll != -1)
		close(_epoll);
}

void	Server::loop() {
	std::map<int, std::string> clientBuffers;
	int clientSocket = -1;
	while (!sig_caught)
	{
		std::string buffer;
		buffer.resize(1024);
		int n_events = epoll_wait(_epoll, _events, 10, -1);
		if (n_events == -1) {
			std::cerr << "Error: epoll_wait()\n";
			break;
		}
		for (int i = 0; i < n_events; ++i) {
			if (_events[i].data.fd == _socket) {
				clientSocket = accept(_socket, NULL, NULL);
				if (clientSocket != -1) {
					fcntl(clientSocket, F_SETFL, O_NONBLOCK);
					epoll_event client_event;
					client_event.events = EPOLLIN;
					client_event.data.fd = clientSocket;
					epoll_ctl(_epoll, EPOLL_CTL_ADD, clientSocket, &client_event);
				}
			} else {
				int clientFd = _events[i].data.fd;
				int bytes = recv(clientFd, &buffer[0], buffer.size() - 1, 0);
				if (bytes > 0) {
					buffer.resize(bytes);
					clientBuffers[clientFd] += buffer;
					std::vector<std::string> messages = extractMessages(clientBuffers[clientFd]);
					for (std::vector<std::string>::iterator it = messages.begin(); it != messages.end(); ++it) {
						Command::processIRCMessage(clientFd, *it);
						if (*it == "CAP LS\r\n")
							continue;
						else if (!getInstance()->_users[clientFd].isPassOk()) {
							std::cout << "* Client fd closed: bad password *\n";
							close(clientFd);
							break;
						}
					}
				} else if (bytes == 0) {
					std::cout << "* Client disconnected *\n";
					clientBuffers.erase(clientFd);
					close(clientFd);
					epoll_ctl(_epoll, EPOLL_CTL_DEL, clientFd, NULL);
				} else {
					std::cout << "Error: recv()\n";
					clientBuffers.erase(clientFd);
					close(clientFd);
					epoll_ctl(_epoll, EPOLL_CTL_DEL, clientFd, NULL);
					break;
				}
			}
		}
	}
	if (clientSocket != -1)
		close(clientSocket);
}

std::map< int, Client >	Server::getClients( void ) {
	return ( getInstance()->_users );
}

Client	*Server::getClientByFD( const int fd ) {
	try {
		return ( &( getInstance()->_users[ fd ] ) );
	} catch ( std::logic_error &e ) {
		return ( NULL );
	}
}

Client	*Server::getClientByNick( std::string nick ) {
	std::map<int, Client> clients = Server::getClients();
	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++) {
		if (it->second.getNickname() == nick) {
			return ( &(getInstance()->_users[ it->first ]) );
		}
	}
	return ( NULL );
}

void	Server::setNicknameByFD( const int fd, const std::string& nickname ) {
	getInstance()->_users[ fd ].setNickname( nickname );
}

void	Server::setHostnameByFD( const int fd, const std::string& hostname ) {
	getInstance()->_users[ fd ].setHostname( hostname );
}

void	Server::setServernameByFD( const int fd, const std::string& servername ) {
	getInstance()->_users[ fd ].setServername( servername );
}

void	Server::setRealnameByFD( const int fd, const std::string& realname ) {
	getInstance()->_users[ fd ].setRealname( realname );
}

void	Server::setUsernameByFD( const int fd, const std::string& username ) {
	getInstance()->_users[ fd ].setUsername( username );
}

void	Server::setNickSetByFD( const int fd, bool status ) {
	getInstance()->_users[ fd ].setNickSet( status );
}

void	Server::setUserSetByFD( const int fd, bool status ) {
	getInstance()->_users[ fd ].setUserSet( status );
}

void	Server::setPassByFD( const int fd, bool status ) {
	getInstance()->_users[ fd ].setPass( status );
}


void	Server::setWelcomeStatusByFD( const int fd, bool status ) {
	getInstance()->_users[ fd ].setWelcomeStatus( status );
}

bool	Server::isClientRegistered( const int fd ) {
	if ((getInstance()->_users[ fd ].isUserSet())
		&& getInstance()->_users[ fd ].isNickSet())
		return (true);
	return (false);
}

bool	Server::isClientPass( const int fd ) {
	return (getInstance()->_users[ fd ].isPassOk());
}

bool	Server::isClientWelcomed( const int fd ) {
	if (getInstance()->_users[ fd ].isWelcomed())
		return (true);
	return (false);
}

const std::string&	Server::getServername( void ) {
	return ( _name );
}

const std::string&	Server::getServPass( void ) {
	return (_password);
}

Channel	*Server::getChannel( const std::string &name ) {
	try {
		return ( &( getInstance()->_channels[ name ] ) );
	} catch ( std::logic_error &e ) {
		return ( NULL );
	}
}

void	Server::addChannel( Channel& channel ) {
	std::string	name = channel.getName();
	for( std::map< std::string, Channel >::iterator it = this->_channels.begin(); it != this->_channels.end(); it++ ) {
		if ( it->first == name ) {
			return ;
		}
	}
	this->_channels[ name ] = channel;
	LOGC( INFO ) << "New channel added to the server: " << channel;
}

void	Server::delChannel( Channel& channel ) {
	for( std::map< std::string, Channel >::iterator it = this->_channels.begin(); it != this->_channels.end(); it++ ) {
		if ( it->first == channel.getName() ) {
			this->_channels.erase( it );
			return ;
		}
	}
}

bool	Server::isChannelExist( const Channel& channel ) {
	if ( this->_channels.find( channel.getName() ) != this->_channels.end() )
		return ( true );
	return ( false );
}

bool	Server::isChannelExist( const std::string& name ) {
	if ( this->_channels.find( name ) != this->_channels.end() )
		return ( true );
	return ( false );
}

void	Server::delClient(int fd) {
	getInstance()->_users.erase(fd);
	close(fd);
}
