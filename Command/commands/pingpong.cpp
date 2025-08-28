#include "./../../Command/Command.hpp"

void	Command::pingCommand( const CommandData_t& data ) const {
	std::string answer = "PONG " + data.message.substr(5) + "\r\n";
	if (send(data.fd, answer.c_str(), answer.size(), 0) == -1) {
		std::cout << "error during pong\n";
	}
	std::cout << GRE "<<< " END << answer;
}
