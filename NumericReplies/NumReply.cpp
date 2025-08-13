#include "NumReply.hpp"

NumReply* NumReply::_instance;

NumReply::NumReply() {
	init();
}

NumReply::~NumReply() {
	delete NumReply::_instance;
}

NumReply *NumReply::GetInstance( void ) {
    if ( NumReply::_instance == NULL ) {
        NumReply::_instance = new NumReply();
    }
    return NumReply::_instance;
}

void	NumReply::init( void ) {
	_list[ 001 ]		=	&func(truc);
}
