/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:51:39 by tclaereb          #+#    #+#             */
/*   Updated: 2025/08/18 06:24:28 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
	#define LEND "\r\n"
#else
	#define LEND "\n"
#endif

// Macro used to call Log() constructor without having to specify the macro used by the Log class.
#define LOG() Log( __FILE__, __PRETTY_FUNCTION__, __LINE__ )
#define LOGC( color ) Log( color, __FILE__, __PRETTY_FUNCTION__, __LINE__ )

// Macro used to customize the Log header.
#define LOGFLAGS( flags ) { Log::logData = flags; }

#define ENABLE_DEBUG() { Log::debug = true; }
#define DISABLE_DEBUG() { Log::debug = false; }

// These are flags used to define what we want to see in the header.
#define FL_FILE Log::logFile
#define FL_FUNC Log::logFunc
#define FL_LINE Log::logLine

#define FL_ALL FL_FILE | FL_FUNC | FL_LINE
#define FL_NONE 0

// Friendly color call.
enum	enumColors {
	LRED,
	LGREEN,
	LYELLOW,
	LBLUE,
	LPURPLE,
	LCYAN,
	LWHITE,
	LDEFAULT,
};

#define WARNING LYELLOW
#define CRITICAL LRED
#define SUCCESS LGREEN
#define INFO LCYAN
#define DEBUG LBLUE

class Log {
	private:
		std::ostringstream			os;
		std::string					_file;
		std::string					_func;
		std::string					_line;
		enumColors					_color;

	public:
		static int const			logFile;
		static int const			logFunc;
		static int const			logLine;

		static int					logData;
		static bool					debug;

		Log( std::string file, std::string func, int line );
		Log( enumColors color, std::string file, std::string func, int line );

		~Log();

		void	displayDebug( enumColors color );

		template<typename T>
		Log &operator<<( T const &msg ) {
			os << msg;
			return ( *this );
		}
};
