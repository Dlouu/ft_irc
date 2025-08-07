#include "Command.hpp"

void	Command::nickCommand( const CommandData_t& data ) const {
	std::string nickname;
	std::cout << "NICK command called" << std::endl;
	(void)data.fd; //faudra s'en servir pour mettre dans la map

	nickname = data.message.substr(5, data.message.length());
	std::cout << "NICK=" << nickname << std::endl;
	//faut remove le antislah n ici et dans USER
}
