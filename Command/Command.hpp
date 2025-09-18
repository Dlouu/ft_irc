#pragma once

#include <vector>
#include <map>
#include <ctype.h>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <netinet/in.h>

#include "../colors.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "NumReply.hpp"
#include "Log.hpp"
#include "Channel.hpp"

typedef struct CommandData_s {
	std::string	message;
	int			fd;
} CommandData_t;

class Command
{
	private:

		static Command*	_instance;
		std::map<std::string, void( Command::* )( const CommandData_t& ) const> _command;

		void	kickCommand( const CommandData_t& data ) const;
		void	modeCommand( const CommandData_t& data ) const;
		void	nickCommand( const CommandData_t& data ) const;
		void	userCommand( const CommandData_t& data ) const;
		void	pingCommand( const CommandData_t& data ) const;
		void	passCommand( const CommandData_t& data ) const;
		void	joinCommand( const CommandData_t& data ) const;
		void	partCommand( const CommandData_t& data ) const;
		void	topicCommand( const CommandData_t& data ) const;
		void	inviteCommand( const CommandData_t& data ) const;
		void	privmsgCommand( const CommandData_t& data ) const;
		void	quitCommand( const CommandData_t& data ) const;

		void	init( void );
		void	notaCommand( void ) const;

		Command();

	public:

		~Command();
		static Command*	getInstance( void );
		void			handleCommand( const CommandData_t& data );
		static void		processIRCMessage(int fd, const std::string& message );
		std::vector< std::string > split( const std::string &str, const char delimiter ) const;
};
