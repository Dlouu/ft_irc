#include "Command.hpp"

void	Command::inviteCommand( const CommandData_t& data ) const {
	(void)data;
	//if (!invitee || !channel)
		//ERR_NEEDMOREPARAMS
	//if (client not on channel)
		//ERR_NOTONCHANNEL
	//else if (client not OP in channel in mode +i)
		//ERR_CHANOPRIVSNEEDED	
	//else if (invitee not in databse)
		//ERR_NOSUCHNICK
	//else if (invitee already in channel)
		//ERR_USERONCHANNEL
	//else 
		//send(RPL_INVITING)
		//if (invitee_status == away)
			//send(RPL_AWAY)
}
