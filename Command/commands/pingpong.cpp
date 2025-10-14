#include "Command.hpp"

void	Command::pingCommand( const CommandData_t& data ) const {
	std::string answer = "PONG " + data.message.substr(5);
	LOGC( SERVER ) << answer;
	answer += "\r\n";
	if (send(data.fd, answer.c_str(), answer.size(), MSG_DONTWAIT) == -1) {
		std::cout << "error during pong\n";
	}
}
