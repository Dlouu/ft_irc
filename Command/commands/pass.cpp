#include "./../../Command/Command.hpp"

void	Command::passCommand(const CommandData_t& data) const {
	(void)data;
	//verify that PASS is the very first command from clients
	//if (password empty)
		//ERR_NEEDMOREPARAMS
	//else if (client already registered)
		//ERR_ALREADYREGISTRED
}