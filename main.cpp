#include "server.hpp"

void processIRCMessage(int clientFd, const std::string& message) {
	std::cout << ">>> " << message;
	
	std::string cleanMessage = message;
	if (cleanMessage.size() >= 2 && cleanMessage.substr(cleanMessage.size() - 2) == "\r\n") {
		cleanMessage = cleanMessage.substr(0, cleanMessage.size() - 2);
	}
	
	std::string response;
	if (cleanMessage == "CAP LS") {
		response = "CAP * LS :\r\n";
		std::cout << "<<< " << response;
		send(clientFd, response.c_str(), response.length(), 0);
	}
}



int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	int port = atoi(argv[1]);
	std::string password = argv[2];

//init start
	//init socket
	int serverSocket = 0;
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 6)) == -1)
		return (std::cerr << "Error during socket creation\n", 1);
	if (fcntl(serverSocket, F_SETFL, O_NONBLOCK) == -1) {
		std::cerr << "Error: serverSocker: fnctl()\n";
		return (1);
	}

	//init address
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress))) {
		std::cerr << "Error: serverSocker: bind()\n";
		close(serverSocket);
		return (1);
	}
	if (listen(serverSocket, 1024)) {
		std::cerr << "Error: serverSocker: listen()\n";
		close(serverSocket);
		return (1);
	}
	
	int epoll = epoll_create1(0);
	if (epoll < 0) {
		std::cerr << "Error: epoll_create1()\n";
		close(serverSocket);
	}

	//init events
	epoll_event event, events[10];
	event.events = EPOLLIN;
	event.data.fd = serverSocket;
	if (epoll_ctl(epoll, EPOLL_CTL_ADD, serverSocket, &event)) {
		std::cerr << "Error: first epoll_ctl()\n";
		close(serverSocket);
		return (1);
	}
//init end
	std::map<int, std::string> clientBuffers;
	int clientSocket;
	while (1)
	{
		std::string buffer;
		buffer.resize(1024);
		int n_events = epoll_wait(epoll, events, 10, -1);
		if (n_events == -1) {
			std::cerr << "Error: epoll_wait()\n";
			close(serverSocket);
			close(clientSocket);
			return (1);
		}
		for (int i = 0; i < n_events; ++i) {
			if (events[i].data.fd == serverSocket) {
				clientSocket = accept(serverSocket, NULL, NULL);
				if (clientSocket != -1) {
					fcntl(clientSocket, F_SETFL, O_NONBLOCK);
					epoll_event client_event;
					client_event.events = EPOLLIN;
					client_event.data.fd = clientSocket;
					epoll_ctl(epoll, EPOLL_CTL_ADD, clientSocket, &client_event);
				}
			} else {
				int clientFd = events[i].data.fd;
				int bytes = recv(clientFd, &buffer[0], buffer.size() - 1, 0);
				if (bytes > 0) {
					buffer.resize(bytes);
					clientBuffers[clientFd] += buffer;
					std::vector<std::string> messages = extractMessages(clientBuffers[clientFd]);
					for (std::vector<std::string>::iterator it = messages.begin(); it != messages.end(); ++it) {
						processIRCMessage(clientFd, *it);
					}
					
				} else if (bytes == 0) {
					std::cout << "* Client disconnected *\n";
					clientBuffers.erase(clientFd);
					close(clientFd);
					epoll_ctl(epoll, EPOLL_CTL_DEL, clientFd, NULL);
				} else {
					std::cout << "Error: recv()\n";
					clientBuffers.erase(clientFd);
					close(clientFd);
					epoll_ctl(epoll, EPOLL_CTL_DEL, clientFd, NULL);
				}
			}
		}
	}
	close(serverSocket);
	exit(EXIT_SUCCESS);
}
