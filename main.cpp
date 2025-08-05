#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <string>
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
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	listen(serverSocket, 1024);
	
	//int	bufferfd = 0;
	int epoll = epoll_create(1);
	epoll_event event, events[10];

	event.events = EPOLLIN;
	event.data.fd = serverSocket;
	epoll_ctl(epoll, EPOLL_CTL_ADD, serverSocket, &event);
	
	int client_socket;
	while (1)
	{
		std::string buffer;
		buffer.resize(1024);
		int n_events = epoll_wait(epoll, events, 10, -1);
		for (int i = 0; i < n_events; ++i) {
			if (events[i].data.fd == serverSocket) {
				client_socket = accept(serverSocket, NULL, NULL);
				epoll_event client_event;
				client_event.events = EPOLLIN;
				client_event.data.fd = client_socket;
				epoll_ctl(epoll, EPOLL_CTL_ADD, client_socket, &client_event);
				/* int bytes = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
				if (bytes > 0) {
					buffer[bytes] = '\0';
					std::cout << buffer;
				} else if (bytes == 0) {
					std::cout << "Client disconnected\n";
					close(client_socket);
				} else {
					std::cout << "recv error1\n";
				} */
			} else {
				int bytes = recv(events[i].data.fd, &buffer[0], buffer.size() - 1, 0);
				if (bytes > 0) {
					buffer.resize(bytes);
					std::cout << buffer;
					//TEMPORARIRE !!!! FAIRE PARSING A PARTIR DE LA
					std::string response;
					if (buffer == "CAP LS 302") {
						response = "CAP * LS :";
						send(events[i].data.fd, response.c_str(), response.length(), 0);
					}
    				send(events[i].data.fd, response.c_str(), response.length(), 0);
					//----------------------------------------------------------------
				} else if (bytes == 0) {
					std::cout << "Client disconnected\n";
					close(client_socket);
				} else {
					std::cout << "recv error2\n";
				}
			}
		}
	}
	close(serverSocket);
}