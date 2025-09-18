#include "Command.hpp"

void	Command::joinCommand( const CommandData_t& data ) const {

	Server	*server = Server::getInstance();
	Client	*executor = server->getClientByFD( data.fd );
	if ( !executor )
		return ;

	std::string cleanMsg = data.message.substr( 5, data.message.size() - 5 );
	LOGC( INFO ) << data.message;
	LOGC( INFO ) << cleanMsg;

	std::vector< std::string > canalsData = this->split( cleanMsg, ' ' );
	std::vector< std::string > channels = this->split( canalsData[ 0 ], ',' );
	std::vector< std::string > passwords;

	if ( canalsData.size() > 1 ) {
		passwords = this->split( canalsData[ 1 ], ',' );
	}

	for ( size_t i = 0; i < channels.size(); i++ ) {
		if ( server->isChannelExist( channels[ i ] ) ) {
			Channel	*channelObj = NULL;
			LOGC( INFO ) << "Channel exist";
			channelObj = server->getChannel( channels[ i ] );
			g_vars[ "channel" ] = channelObj->getName();
			if ( passwords.size() > 0 && ( i >= passwords.size() || !channelObj->isPasswordCorrect( passwords[ i ] ) ) ) {
				sendReply( executor->getFD(), ERR_BADCHANNELKEY );
				continue;
			}
			channelObj->addUser( *server, *executor );
		} else {
			LOGC( INFO ) << "Channel doesn't exist";
			Channel	channelObj = Channel( channels[ i ] );
			channelObj.addUser( *server, *executor );
			channelObj.addOperator( *server, *executor );
			server->addChannel( channelObj );
		}
	}
	//if (no client or no channel param)
		//ERR_NEEDMOREPARAMS
	//else if (channel mode is +i (invite only))
		//ERR_INVITEONLYCHAN
	//else if (channel doesn't exit)
		//ERR_NOSUCHCHANNEL
	//else if (channel name isn't in good format (e.g. no '#' before channel name)) A valid channel name typically:
		//ERR_BADCHANMASK	// Begins with # or &
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
