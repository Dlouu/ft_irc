#include "Command.hpp"

void	Command::kickCommand( const CommandData_t& data ) const {
	(void)data;
	//if (no target or no channel)
		//ERR_NEEDMOREPARAMS
	//else if (channel name isn't in good format (e.g. no '#' before channel name)) A valid channel name typically:
		//ERR_BADCHANMASK														// Begins with # or &
																				// Has 1–200 characters
																				// Cannot contain spaces, ASCII BEL (0x07), comma ,, or the channel type prefixes # / & / + / ! inside
																				// Wildcards (*, ?) are generally not allowed unless specifically implemented for masks 
																				//source : chat gpt t'inquiete
	//else if (client not on channel)
		//ERR_NOTONCHANNEL
	//else if (channel not in data)
		//ERR_NOSUCHCHANNEL
	//else if (client is OP on channel)
		//ERR_CHANOPRIVSNEEDED
	//else 
		//kick target from server data
		//send(<kicker>!<user>@<host> KICK <channel> <target> :<reason>)
}