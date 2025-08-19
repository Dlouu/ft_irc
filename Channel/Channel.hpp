/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 08:18:40 by tclaereb          #+#    #+#             */
/*   Updated: 2025/08/19 10:59:36 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <algorithm>

class Channel {
	private:
		const std::string	_name;
		std::string			_topic;
		std::string			_password;
		unsigned long		_userLimit;
		std::vector< int >	_operators;

		bool				_inviteOnly;

	public:
		Channel( const std::string &name, const std::string &pass );

		const std::string			&getName( void ) const;
		const bool					&getInviteOnly( void ) const;
		const unsigned long			&getUserLimit( void ) const;
		const std::vector< int >	&getOperators( void ) const;


		void						setInviteOnly( const bool state );
		void						setUserLimit( const unsigned long n );
		void						setPassword( const std::string password );

		void						addOperator( const int fd );
		void						delOperator( const int fd );
};
