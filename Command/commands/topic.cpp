#include "Command.hpp"

void	Command::topicCommand( const CommandData_t& data ) const {
	(void)data;
	//if (<channel> is empty)
		//ERR_NEEDMOREPARAMS
	//else if (<topic> empty AND topic data is empty)
		//RPL_NOTOPIC
	//else if (channel mode +t AND client not OP)
		//ERR_CHANOPRIVSNEEDED
	//else if (client not in channel)
		//ERR_NOTONCHANNEL
	//else
		//change topic message in database
		//RPL_TOPIC
}
