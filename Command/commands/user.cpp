#include "./../../Command/Command.hpp"

void	Command::userCommand( const CommandData_t& data ) const {
	std::string	user;
	std::string	realname;
	std::string	s;
	size_t		realnamePos;

	user = data.message.substr( 5, data.message.length() );

	if (Server::isUserRegistered( data.fd ))
		return sendReply( data.fd, ERR_ALREADYREGISTRED );

	// Set Realname
	if ((realnamePos = user.find(":") + 1) == std::string::npos)
		return sendReply( data.fd, ERR_NEEDMOREPARAMS );
	realname = user.substr( realnamePos, user.length() );
	Server::setRealnameByFD( data.fd, realname );

	s = user.substr(0, realnamePos);
	std::vector<std::string> param = this->split( s, ' ' );
	if (param.size() != 4)
		return sendReply( data.fd, ERR_NEEDMOREPARAMS );
	if ((param.size() == 4) && param[3] != ":")
		return sendReply( data.fd, ERR_NEEDMOREPARAMS );

	// Set User, Host and Server names
	Server::setUsernameByFD( data.fd, param[0] );
	Server::setHostnameByFD( data.fd, param[1] );
	Server::setServernameByFD( data.fd, param[2] );
	Server::setUserSetByFD( data.fd, true );

	sendReply( data.fd, RPL_WELCOME );
	sendReply( data.fd, RPL_YOURHOST );
	sendReply( data.fd, RPL_CREATED );
	sendReply( data.fd, RPL_MYINFO );

	// Send MOTD
	sendReply( data.fd, RPL_MOTDSTART );
	sendReply( data.fd, RPL_MOTD );
	sendReply( data.fd, RPL_ENDOFMOTD );
}

	//NOTES:
	//if (!<username> OR !<hostname> OR !<servername> OR !<realname>)
		//ERR_NEEDMOREPARAMS
	//else if (user already connected)
		//ERR_ALREADYREGISTRED
