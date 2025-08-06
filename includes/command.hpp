#pragma once

#include <string>
#include <iostream>
#include <netinet/in.h>

class Command
{
	private:
		void	kickCommand( void ) const;
		void	inviteCommand( void ) const;
		void	topicCommand( void ) const;
		void	modeCommand( void ) const;
		void	capCommand( void ) const;
		void	nickCommand( void ) const;
		void	userCommand( void ) const;
		void	privmsgCommand( void ) const;
		void	pingCommand( void ) const;
		void	pongCommand( void ) const;
		void	joinCommand( void ) const;
		
	public:
		Command();
		~Command();

		static void	handleCommand( std::string command, int fd );
};
