#include "Command.hpp"

void	Command::modeCommand( const CommandData_t& data ) const {
	// Channel	*channel =;

	// if (client isn't in channel database)
	// 	return sendReply( data.fd, ERR_NOTONCHANNEL );
	// else if (only 1 param)
	// 	if (param == channel database)
	// 		return sendReply( data.fd, RPL_CHANNELMODEIS );
	// 	else if (param == client nickname)
	// 		return sendReply( data.fd, RPL_UMODEIS ); (+ client modes)
	// 	else
	// 		return sendReply( data.fd, ERR_NOSUCHCHANNEL );
	// else if(!channel OR !flag/mods)
	// 	return sendReply( data.fd, ERR_NEEDMOREPARAMS );
	
	// if (flags/modes != i OR j OR t OR o OR k OR l)
	// 	return sendReply( data.fd, ERR_UMODEUNKNOWNFLAG );

	// if (channel not in database)
	// 	return sendReply( data.fd, ERR_NOSUCHCHANNEL );
	// else if (client not OP)
	// 	return sendReply( data.fd, ERR_CHANOPRIVSNEEDED );
	// if (flag/mods == o AND !target)
	// 	return sendReply( data.fd, ERR_NEEDMOREPARAMS );
	// 	else if (target not in channel data)
	// 		return sendReply( data.fd, ERR_NOTONCHANNEL );
	// 	else if ("+o")
	// 		promote target to OP + message saying "+o target" ON CHANNEL
	// 	else if ("-o")
	// 		demote target from OP + message saying "-o target" ON CHANNEL
	// else if (flags/mods == i)
	// 	message telling channel is +i or -i on channel
	// else if (flags == t)
	// 	message telling channel is +t or -t on channel
	// else if (flag ==  k)
	// 	if (flag == +k AND !pass)
	// 		return sendReply( data.fd, ERR_NEEDMOREPARAMS );
	// 	else if (flag == +k AND new pass == old pass)
	// 		return sendReply( data.fd, ERR_KEYSET );
	// 	else
	// 		:irc.example.net MODE #chatroom +k secret
	// else if (flag == l)
	// 	if (+l AND !limit)
	// 		return sendReply( data.fd, ERR_NEEDMOREPARAMS );
	// 	else if ("+l")
	// 		set user limit to limit : :irc.example.net MODE #chatroom +l 10
	// 	else
	// 		remove set limit 

	// ERR_NOSUCHNICK ??
	// ERR_UNKNOWNMODE meh
}

	//NOTES :

	//if (client isn't in channel database)
		//ERR_NOTONCHANNEL
	//else if (only 1 param)
		//if (param == channel database)
			//RPL_CHANNELMODEIS
		//else if (param == client nickname)
			//RPL_UMODEIS (+ client modes)
		//else
			//ERR_NOSUCHCHANNEL
	//else if(!channel OR !flag/mods)
		//ERR_NEEDMOREPARAMS
	
	//if (flags/modes != i OR j OR t OR o OR k OR l)
		//ERR_UMODEUNKNOWNFLAG

	//if (channel not in database)
		//ERR_NOSUCHCHANNEL
	//else if (client not OP)
		//ERR_CHANOPRIVSNEEDED
	//if (flag/mods == o AND !target)
		//ERR_NEEDMOREPARAMS
		//else if (target not in channel data)
			//ERR_NOTONCHAMNNEL
		//else if ("+o")
			//promote target to OP + message saying "+o target" ON CHANNEL
		//else if ("-o")
			//demote target from OP + message saying "-o target" ON CHANNEL
	//else if (flags/mods == i)
		//message telling channel is +i or -i on channel
	//else if (flags == t)
		//message telling channel is +t or -t on channel
	//else if (flag ==  k)
		//if (flag == +k AND !pass)
			//ERR_NEEDMOREPARAMS
		//else if (flag == +k AND new pass == old pass)
			//ERR_KEYSET
		//else
			//:irc.example.net MODE #chatroom +k secret
	//else if (flag == l)
		//if (+l AND !limit)
			//ERR_NEEDMOREPARAMS
		//else if ("+l")
			//set user limit to limit : :irc.example.net MODE #chatroom +l 10
		//else
			//remove set limit 


	//ERR_NOSUCHNICK ??
	//ERR_UNKNOWNMODE meh

/* MODE - Change the channel’s mode:
· i: Set/remove Invite-only channel
· t: Set/remove the restrictions of the TOPIC command to channel operators
· k: Set/remove the channel key (password)
· o: Give/take channel operator privilege
· l: Set/remove the user limit to channel */

// ░▒▓████████▓▒░▒▓███████▓▒░ ░▒▓██████▓▒░░▒▓███████▓▒░       ░▒▓███████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓███████▓▒░  
//    ░▒▓█▓▒░   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ 
//    ░▒▓█▓▒░   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ 
//    ░▒▓█▓▒░   ░▒▓███████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓███████▓▒░       ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓███████▓▒░  
//    ░▒▓█▓▒░   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ 
//    ░▒▓█▓▒░   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ 
//    ░▒▓█▓▒░   ░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░             ░▒▓███████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░ 