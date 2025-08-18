#include "./../../Command/Command.hpp"

void	Command::privmsgCommand( const CommandData_t& data ) const {
	(void)data;
	//if (no target)
		//ERR_NORECIPIENT
	//else if (not in channel OR client banned from channel OR (channel mode is invite only AND client isn't invited) OR (channel mode is +m AND client IS NOT (+o OR +v)))
		//ERR_CANNOTSENDTOCHAN
	//else if (channel prfix is wrong)
		//ERR_WILDTOPLEVEL
		//The “top-level” refers to the first character of the channel name — channels must start with valid prefixes like #, &, +, or ! and cannot start with a wildcard.
	//else if (no channel prefix)
		//ERR_NOTOPLEVEL
	//else if (target nickname is not in database)
		//ERR_NOSUCHNICK
	//else if (<message> is empty)
		//ERR_NOTEXTTOSEND
	//else if (target count > channel allowed targets)
		//ERR_TOOMANYTARGETS
	//else {
		//while (target count--) {
			//send(msg to target)
			//if (target is away)
				//send(RPLY_AWAY to client);
		//}
	//}
}
