#include "parsing.hpp"
#include "Command.hpp"
#include "Colors.hpp"
#include <algorithm>

void processIRCMessage( int fd, const std::string& message ) {
	
	std::cout << YEL ">>> " PUR << message << END;
	
	std::string cleanMessage = message;
	if (cleanMessage.size() >= 2 && cleanMessage.substr(cleanMessage.size() - 2) == "\r\n") {
		cleanMessage = cleanMessage.substr(0, cleanMessage.size() - 2);
	}
	Command::GetInstance()->handleCommand((CommandData_t){cleanMessage, fd});
}
