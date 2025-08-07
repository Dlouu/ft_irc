#pragma once

#include <string>
#include <iostream>
#include <netinet/in.h>
#include <map>

typedef struct CommandData_s {
	std::string	message;
	int			fd;
} CommandData_t;

class Command
{
	private:

		std::map<std::string, void(Command::*)( const CommandData_t& ) const> _command;
		static Command*	_instance;

		void	kickCommand( const CommandData_t& data ) const;
		void	inviteCommand( const CommandData_t& data ) const;
		void	topicCommand( const CommandData_t& data ) const;
		void	modeCommand( const CommandData_t& data ) const;
		void	capCommand( const CommandData_t& data ) const;
		void	nickCommand( const CommandData_t& data ) const;
		void	userCommand( const CommandData_t& data ) const;
		void	privmsgCommand( const CommandData_t& data ) const;
		void	pingCommand( const CommandData_t& data ) const;
		void	pongCommand( const CommandData_t& data ) const;
		void	joinCommand( const CommandData_t& data ) const;

		void	init( void );
		void	notaCommand( void ) const;

		Command();
		~Command();
		
	public:
	
		static Command*	GetInstance( void );
		void			handleCommand( const CommandData_t& data );
};
