#pragma once

#include <iostream>
#include <string>
#include <netinet/in.h>

void processIRCMessage(int fd, const std::string& message);