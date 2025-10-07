#include "NumReply.hpp"

std::map<int, std::string> createReplies() {
	std::map<int, std::string> num;

	num[RPL_WELCOME]			= ":{server} 001 {nick} :Welcome to the IRC Network {mask}\r\n";
	num[RPL_YOURHOST]			= ":{server} 002 {nick} :Your host is {server}, running version {version}\r\n";
	num[RPL_CREATED]			= ":{server} 003 {nick} :This server was created {datetime}\r\n";
	num[RPL_MYINFO]				= ":{server} 004 {nick} {server} {version} itkol\r\n";

	num[RPL_UMODEIS]			= ":{server} 221 {nick} {modes}\r\n";
	num[RPL_AWAY]				= ":{server} 301 {nick} {target} :{message}\r\n";
	num[RPL_CHANNELMODEIS]		= ":{server} 324 {nick} {channel} +{modes} {params}\r\n";
	num[RPL_NOTOPIC]			= ":{server} 331 {nick} {channel} :No topic is set\r\n";
	num[RPL_TOPIC]				= ":{server} 332 {nick} {channel} :{topic}\r\n";
	num[RPL_INVITING]			= ":{server} 341 {nick} {target} {channel}\r\n";
	num[RPL_NAMREPLY]			= ":{server} 353 {nick} = {channel} :{names}\r\n";
	num[RPL_ENDOFNAMES]			= ":{server} 366 {nick} {channel} :End of /NAMES list\r\n";

	num[RPL_MOTDSTART]			= ":{server} 375 {nick} :- {server} Message of the day -\r\n";
	num[RPL_MOTD]				= ":{server} 372 {nick} :- {motd}\r\n";
	num[RPL_ENDOFMOTD]			= ":{server} 376 {nick} :End of /MOTD command\r\n";

	num[ERR_NOSUCHNICK]			= ":{server} 401 {nick} {target} :No such nick/channel\r\n";
	num[ERR_NOSUCHCHANNEL]		= ":{server} 403 {nick} {channel} :No such channel\r\n";
	num[ERR_CANNOTSENDTOCHAN]	= ":{server} 404 {nick} {channel} :Cannot send to channel\r\n";
	num[ERR_TOOMANYCHANNELS]	= ":{server} 405 {nick} {channel} :You have joined too many channels\r\n";
	num[ERR_TOOMANYTARGETS]		= ":{server} 407 {nick} {target} :Duplicate recipients. No message delivered\r\n";
	num[ERR_NORECIPIENT]		= ":{server} 411 {nick} :No recipient given ({command})\r\n";
	num[ERR_NOTEXTTOSEND]		= ":{server} 412 {nick} :No text to send\r\n";
	num[ERR_NOTOPLEVEL]			= ":{server} 413 {nick} {mask} :No toplevel domain specified\r\n";
	num[ERR_WILDTOPLEVEL]		= ":{server} 414 {nick} {mask} :Wildcard in toplevel domain\r\n";

	num[ERR_NONICKNAMEGIVEN]	= ":{server} 431 {nick} :No nickname given\r\n";
	num[ERR_ERRONEUSNICKNAME]	= ":{server} 432 {nick} :Erroneous nickname\r\n";
	num[ERR_NICKNAMEINUSE]		= ":{server} 433 {nick} :Nickname is already in use\r\n";
	num[ERR_USERNOTINCHANNEL]	= ":{server} 441 {nick} {target} {channel}: They aren't on that channel\r\n";
	num[ERR_NOTONCHANNEL]		= ":{server} 442 {nick} {channel} :You're not on that channel\r\n";
	num[ERR_USERONCHANNEL]		= ":{server} 443 {nick} {target} {channel} :is already on channel\r\n";
	num[ERR_NEEDMOREPARAMS]		= ":{server} 461 {nick} {command} :Not enough parameters\r\n";
	num[ERR_ALREADYREGISTRED]	= ":{server} 462 {nick} :You may not reregister\r\n";
	num[ERR_KEYSET]				= ":{server} 467 {nick} {channel} :Channel key already set\r\n"; // a tester
	num[ERR_CHANNELISFULL]		= ":{server} 471 {nick} {channel} :Cannot join channel (+l)\r\n"; // a tester
	num[ERR_INVITEONLYCHAN]		= ":{server} 473 {nick} {channel} :Cannot join channel (+i)\r\n"; // a tester
	num[ERR_BANNEDFROMCHAN]		= ":{server} 474 {nick} {channel} :Cannot join channel (+b)\r\n"; // a tester
	num[ERR_BADCHANNELKEY]		= ":{server} 475 {nick} {channel} :Cannot join channel (+k)\r\n"; // a tester
	num[ERR_BADCHANMASK]		= ":{server} 476 {nick} {channel} :Bad Channel Mask\r\n"; // a tester
	num[ERR_CHANOPRIVSNEEDED]	= ":{server} 482 {channel} :You're not channel operator\r\n";
	num[ERR_UMODEUNKNOWNFLAG]	= ":{server} 501 {nick} :Unknown MODE flag\r\n";

    return num;
}

std::map<std::string, std::string> fillPermanentVars( void ) {
	std::map<std::string, std::string> tab;

	tab[ "server" ]		= Server::getServername();
	tab[ "datetime" ]	= Server::getInstance()->datetime;
	tab[ "version" ]	= SERVER_VERSION;
	tab[ "command" ]	= "";
	tab[ "channel" ]	= "";
	tab[ "topic" ]		= "";
	tab[ "target" ]		= "";
	tab[ "reason" ]		= "";
	tab[ "modes" ]		= "";
	tab[ "params" ]		= "";
	tab[ "motd" ]		= 	"attention les yeux !\n\n" \
							"⡆⣐⢕⢕⢕⢕⢕⢕⢕⢕⠅⢗⢕⢕⢕⢕⢕⢕⢕⠕⠕⢕⢕⢕⢕⢕⢕⢕⢕⢕\n" \
							"⢐⢕⢕⢕⢕⢕⣕⢕⢕⠕⠁⢕⢕⢕⢕⢕⢕⢕⢕⠅⡄⢕⢕⢕⢕⢕⢕⢕⢕⢕\n" \
							"⢕⢕⢕⢕⢕⠅⢗⢕⠕⣠⠄⣗⢕⢕⠕⢕⢕⢕⠕⢠⣿⠐⢕⢕⢕⠑⢕⢕⠵⢕\n" \
							"⢕⢕⢕⢕⠁⢜⠕⢁⣴⣿⡇⢓⢕⢵⢐⢕⢕⠕⢁⣾⢿⣧⠑⢕⢕⠄⢑⢕⠅⢕\n" \
							"⢕⢕⠵⢁⠔⢁⣤⣤⣶⣶⣶⡐⣕⢽⠐⢕⠕⣡⣾⣶⣶⣶⣤⡁⢓⢕⠄⢑⢅⢑\n" \
							"⠍⣧⠄⣶⣾⣿⣿⣿⣿⣿⣿⣷⣔⢕⢄⢡⣾⣿⣿⣿⣿⣿⣿⣿⣦⡑⢕⢤⠱⢐\n" \
							"⢠⢕⠅⣾⣿⠋⢿⣿⣿⣿⠉⣿⣿⣷⣦⣶⣽⣿⣿⠈⣿⣿⣿⣿⠏⢹⣷⣷⡅⢐\n" \
							"⣔⢕⢥⢻⣿⡀⠈⠛⠛⠁⢠⣿⣿⣿⣿⣿⣿⣿⣿⡀⠈⠛⠛⠁⠄⣼⣿⣿⡇⢔\n" \
							"⢕⢕⢽⢸⢟⢟⢖⢖⢤⣶⡟⢻⣿⡿⠻⣿⣿⡟⢀⣿⣦⢤⢤⢔⢞⢿⢿⣿⠁⢕\n" \
							"⢕⢕⠅⣐⢕⢕⢕⢕⢕⣿⣿⡄⠛⢀⣦⠈⠛⢁⣼⣿⢗⢕⢕⢕⢕⢕⢕⡏⣘⢕\n" \
							"⢕⢕⠅⢓⣕⣕⣕⣕⣵⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣷⣕⢕⢕⢕⢕⡵⢀⢕⢕\n" \
							"⢑⢕⠃⡈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢃⢕⢕⢕\n" \
							"⣆⢕⠄⢱⣄⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢁⢕⢕⠕⢁\n" \
							"⣿⣦⡀⣿⣿⣷⣶⣬⣍⣛⣛⣛⡛⠿⠿⠿⠛⠛⢛⣛⣉⣭⣤⣂⢜⠕⢑⣡⣴⣿\n";
    return tab;
}

std::map<std::string, std::string> fillVars( int clientFD, std::map<std::string, std::string> tab ) {

	Client client	= *Server::getClientByFD( clientFD );
	tab[ "nick" ]	= client.getNickname();
	tab[ "user" ]	= client.getUsername();
	tab[ "host" ]	= client.getHostname();
	tab[ "mask" ]	= client.getMask();
    return tab;
}

std::string formatReply( const int code, const std::map<std::string, std::string> &vars ) {
	std::map< int, std::string >::const_iterator templateIt = g_replies.find( code );
	if ( templateIt == g_replies.end() )
		return ( "" );
	std::string reply = templateIt->second;

	std::map<std::string, std::string>::const_iterator it;
	for ( it = vars.begin(); it != vars.end(); ++it ) {
		std::string key = "{" + it->first + "}";
		std::string	value = it->second;

		std::string::size_type pos = 0;
		while ( ( pos = reply.find( key, pos ) ) != std::string::npos ) {
			reply.replace( pos, key.length(), value );
			pos += value.length();
		}
	}
	return reply;
}

void sendReply( const int fd, int code ) {
	g_vars = fillVars( fd , g_vars );
	std::string reply = formatReply( code, g_vars );
	if ( send( fd, reply.c_str(), reply.length(), 0 ) == -1 ) {
		std::cerr << RED "Error sending response" END << std::endl;
	}
	LOGC( SERVER ) << reply;
}

std::string formatMessage( std::string message, const std::map<std::string, std::string> &vars ) {

	std::map<std::string, std::string>::const_iterator it;
	for ( it = vars.begin(); it != vars.end(); ++it ) {
		std::string key = "{" + it->first + "}";
		std::string	value = it->second;

		std::string::size_type pos = 0;
		while ( ( pos = message.find( key, pos ) ) != std::string::npos ) {
			message.replace( pos, key.length(), value );
			pos += value.length();
		}
	}
	return message;
}

void sendMessage( const int fd, std::string str ) {
	g_vars = fillVars( fd , g_vars );
	std::string message = formatMessage( str + "\r\n", g_vars );
	if ( send( fd, message.c_str(), message.length(), 0 ) == -1 ) {
		std::cerr << RED "Error sending response" END << std::endl;
	}
	LOGC( SERVER ) << message;
}
