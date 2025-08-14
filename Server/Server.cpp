#include "Server.hpp"

Server	*Server::_instance;

std::vector<std::string> extractMessages(std::string& buffer) {
	std::vector<std::string> messages;
	size_t pos = 0;

	while ((pos = buffer.find("\r\n")) != std::string::npos) {
		messages.push_back(buffer.substr(0, pos + 2));
		buffer.erase(0, pos + 2);
	}
	return messages;
}

Server *Server::GetInstance( void ) {
    if ( Server::_instance == NULL ) {
        Server::_instance = new Server();
    }
    return Server::_instance;
}

void	Server::DestroyInstance( void ) {
	if (_instance)
		delete _instance;
	_instance = NULL;
	return;
}

Server::Server( void ) {}

void	Server::init(int port) {

	_socket = -1;
	_epoll = -1;

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

std::map< int, Client >	Server::GetClients( void ) {
	return ( GetInstance()->_users );
}

Client	Server::GetClientByFD( const int fd ) {
	return ( GetInstance()->_users[ fd ] );
}

Client	Server::GetClientByNickname( const std::string nickname ) {
	Server *server = GetInstance();
	std::map< int, Client > clients = server->GetClients();

	for ( std::map< int, Client >::iterator it = clients.begin(); it != clients.end(); it++ ) {
		if ( it->second.getNickname() == nickname )
			return ( it->second );
	}

	return ( Client() );
}
