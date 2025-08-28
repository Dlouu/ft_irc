#include "signal.hpp"

volatile sig_atomic_t sig_caught = false;

static void	sigHandler(int sig) {
	sig_caught = true;

	Command *CommandInstance = Command::getInstance();
	delete CommandInstance;
	Server::destroyInstance();

	std::cout << "Server closed manually: " << sig << std::endl;
}

void catch_sig() {
	signal(SIGINT, sigHandler);
}