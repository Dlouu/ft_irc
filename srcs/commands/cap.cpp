#include "Command.hpp"

void	Command::capCommand( const CommandData_t& data ) const {
	std::string response;

	std::cout << "CAP command called" << std::endl;

	if (data.message == "CAP LS") {
		response = "CAP * LS :\r\n";
		std::cout << "<<< " << response;
		if (send(data.fd, response.c_str(), response.length(), 0) == -1) {
			std::cerr << "Error sending response" << std::endl;
		}
	}
}
