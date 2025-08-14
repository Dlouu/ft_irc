#include "./../../Command/Command.hpp"

void	Command::nickCommand( const CommandData_t& data ) const {
	//if (nickname param empty)
		//ERR_NONICKNAMEGIVEN
	//else if (nickname param already in database)
		//ERR_NICKNAMEINUSE
	//else if (invalid nickname)
										// nickname is considered invalid if:
										// It contains spaces.
										// It contains disallowed special characters (varies per server, but often excludes , * ? ! @ . : # & at certain positions).
										// It starts with a character not allowed (most servers require it to start with a letter or special symbol like _ or [ but not a number).
										// It exceeds the maximum length (commonly 9 or 30 characters, depending on server config).
										// It violates server-specific nickname rules. 
		//ERR_ERRONEUSNICKNAME
	//else
		//if (client was not already registered) 
			//register nickname in database
			//client nick set == true
		//else (server 000 :<oldnick>!<user>@<host> NICK :<newnick>)
}
