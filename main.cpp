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

	int epoll = epoll_create(1);
	epoll_event events;

	bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	int client_socket;
	char buffer[1024] = {0};
	listen(serverSocket, 1024);
	while (1)
	{
		epoll_pwait(epoll, &events, 1, 1000, NULL);
		client_socket = accept(serverSocket, NULL, NULL);
		recv(client_socket, buffer, sizeof(buffer), 0);
		std::cout << buffer;
	}
	close(serverSocket);
}