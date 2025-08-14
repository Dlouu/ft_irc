#include "signal.hpp"

volatile sig_atomic_t sig_caught = false;

static void	sigHandler(int sig) {
	sig_caught = true;

	Command *CommandInstance = Command::GetInstance();
	Server *ServerInstance = Server::GetInstance();
	delete ServerInstance;
	delete CommandInstance;

	std::cout << "Server closed manually: " << sig << std::endl;
}


void catch_sig() {
	signal(SIGINT, sigHandler);
}