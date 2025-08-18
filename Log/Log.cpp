/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:51:35 by tclaereb          #+#    #+#             */
/*   Updated: 2025/08/18 06:24:56 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Log.hpp"

int const		Log::logFile = 1;
int const		Log::logFunc = 2;
int const		Log::logLine = 4;

// std::ostream	&Log::os = std::cout;
int				Log::logData = FL_NONE;
bool			Log::debug = true;

std::string const	colors[] = {
	"\033[0;31m",
	"\033[0;32m",
	"\033[0;33m",
	"\033[0;34m",
	"\033[0;35m",
	"\033[0;36m",
	"\033[0;37m",
	"\033[0m",
};

Log::Log( std::string file, std::string func, int line ) {
	this->_color = LDEFAULT;
	std::stringstream	ss;

	ss << line;
	this->_file = logData & logFile ? "./" + file : "";
	this->_func = logData & logFunc ? func : "";
	this->_line = logData & logLine ? ss.str() : "";

	this->displayDebug( LDEFAULT );
}

Log::Log( enumColors color, std::string file, std::string func, int line ) {
	this->_color = color;
	if ( !debug && color == DEBUG )
		return ;

	std::stringstream	ss;
	ss << line;

	this->_file = logData & logFile ? "./" + file : "";
	this->_func = logData & logFunc ? func : "";
	this->_line = logData & logLine ? ss.str() : "";

	this->displayDebug( color );
}

Log::~Log() {
	if ( !debug && this->_color == DEBUG ) {
		return ;
	}


	if ( ( logData & logFile ) && ( logData & logLine ) && ( logData & logFunc ) )
		os << " - \033[3m(" << this->_file << ":" << this->_line << " " << this->_func << ")\033[0m";
	else if ( ( logData & logFile ) && ( logData & logLine ) )
		os << " - \033[3m(" << this->_file << ":" << this->_line << ")\033[0m";
	else if ( ( logData & logFile ) && ( logData & logFunc ) )
		os << " - \033[3m(" << this->_file << " " << this->_func << ")\033[0m";
	else if ( ( logData & logLine ) && ( logData & logFunc ) )
		os << " - \033[3m(" << this->_line << " " << this->_func << ")\033[0m";
	else if ( logData & logFile )
		os << " - \033[3m(" << this->_file << ")\033[0m";
	else if ( logData & logLine )
		os << " - \033[3m(" << this->_line << ")\033[0m";
	else if ( logData & logFunc )
		os << " - \033[3m(" << this->_func << ")\033[0m";

	os << LEND;

	os << colors[ LDEFAULT ];

	std::cout << os.str();
}

void	Log::displayDebug( enumColors color ) {
	os << colors[color] << "[LOG] - ";
}
