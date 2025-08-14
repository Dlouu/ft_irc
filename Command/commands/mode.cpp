#include "./../../Command/Command.hpp"

void	Command::modeCommand( const CommandData_t& data ) const {
	//set message flag = 000;

}


/* MODE - Change the channel’s mode:
· i: Set/remove Invite-only channel
· t: Set/remove the restrictions of the TOPIC command to channel
operators
· k: Set/remove the channel key (password)
· o: Give/take channel operator privilege
· l: Set/remove the user limit to channel */