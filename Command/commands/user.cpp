#include "./../../Command/Command.hpp"

void	Command::userCommand( const CommandData_t& data ) const {
	std::string user;
	std::cout << MAG << "USER command called" END << std::endl;

	user = data.message.substr( 5, data.message.length() );
	std::cout << BLU "USER=" END << user << std::endl;
	sendReply( data.fd, RPL_WELCOME );
}

// DLOU TO DO:
// Quand j'aurais fait les 002-004 et le welcome message,
// je changerai le RPL_WELCOME par un MOTD
// Y'aura un joli ASCII art Uwuesque

//if (!<username> OR !<hostname> OR !<servername> OR 1<realname>)
	//ERR_NEEDMOREPARAMS
//else if (user already connected)
	//ERR_ALREADYREGISTRED