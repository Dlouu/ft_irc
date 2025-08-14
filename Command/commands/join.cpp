#include "./../../Command/Command.hpp"

void	Command::joinCommand( const CommandData_t& data ) const {
	//if (no client or no channel param)
		//ERR_NEEDMOREPARAMS
	//else if (channel mode is +i (invite only))
		//ERR_INVITEONLYCHAN
	//else if (channel doesn't exit)
		//ERR_NOSUCHCHANNEL
	//else if (channel name isn't in good format (e.g. no '#' before channel name)) A valid channel name typically:
		//ERR_BADCHANMASK														// Begins with # or &
																				// Has 1–200 characters
																				// Cannot contain spaces, ASCII BEL (0x07), comma ,, or the channel type prefixes # / & / + / ! inside
																				// Wildcards (*, ?) are generally not allowed unless specifically implemented for masks 
																				//source : chat gpt t'inquiete
	//else if (channel is full)
		//ERR_CHANNELISFULL
	//else if (client is in ban list of the channel)
		//ERR_BANNEDFROMCHAN
	//else if (password is wrong)
		//ERR_BADCHANNELKEY
	//else if (client joined too many channels (>10?))
		//ERR_TOOMANYCHANNELS
	//else 
		//RPL_TOPIC and RPL_NAMREPLY
}
