#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include <cmath>

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	int port = atoi(argv[1]);
	std::string password = argv[2];

	int serverSocket = 0;
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 6)) == -1)
		return (std::cerr << "Error during socket creation\n", 1);
	if (fcntl(serverSocket, F_SETFL, O_NONBLOCK) == -1) {
		std::cerr << "Error: serverSocker: fnctl()\n";
	}

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress))) {
		std::cerr << "Error: serverSocker: bind()\n";
		close(serverSocket);
		exit(EXIT_FAILURE);
	}
	if (listen(serverSocket, 1024)) {
		std::cerr << "Error: serverSocker: listen()\n";
		close(serverSocket);
		exit(EXIT_FAILURE);
	}
	
	int epoll = epoll_create1(0);
	if (epoll < 0) {
		std::cerr << "Error: epoll_create1()\n";
		close(serverSocket);
	}

	epoll_event event, events[10];
	event.events = EPOLLIN;
	event.data.fd = serverSocket;
	if (epoll_ctl(epoll, EPOLL_CTL_ADD, serverSocket, &event)) {
		std::cerr << "Error: first epoll_ctl()\n";
		close(serverSocket);
		exit(EXIT_FAILURE);
	}

	int clientSocket;
	while (1)
	{
		std::string buffer = "";
		buffer.resize(1024);
		int n_events = epoll_wait(epoll, events, 10, -1);
		if (n_events == -1) {
			std::cerr << "Error: epoll_wait()\n";
			close(serverSocket);
			close(clientSocket);
			exit(EXIT_FAILURE);
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
				int bytes = recv(events[i].data.fd, &buffer[0], buffer.size() - 1, 0);
				if (bytes > 0) {
					if (buffer.size() >= 2 && buffer.substr(buffer.size() - 2) == "\r\n") {
						buffer = buffer.substr(0, buffer.size() - 2);
					}
					std::cout << ">>> "<< buffer;
					//TEMPORARIRE !!!! FAIRE PARSING A PARTIR DE LA
					std::string response = "test";
					if (buffer == "CAP LS") {
					//	response = "CAP * LS :\r\n";
						std::cout << "<<< " << response << '\n';
					//	send(events[i].data.fd, response.c_str(), response.length(), 0);
					}
    				//send(events[i].data.fd, response.c_str(), response.length(), 0);
					//----------------------------------------------------------------
				} else if (bytes == 0) {
					std::cout << "* Client disconnected *\n";
					close(clientSocket);
					epoll_ctl(epoll, EPOLL_CTL_DEL, events[i].data.fd, NULL);
				} else {
					std::cout << "Error: recv(\n";
					close(events[i].data.fd);
					epoll_ctl(epoll, EPOLL_CTL_DEL, events[i].data.fd, NULL);
				}
			}
		}
	}
	close(serverSocket);
	exit(EXIT_SUCCESS);
}
