#pragma once

#include <iostream>
#include <string>
#include <netinet/in.h>

void processIRCMessage(int clientFd, const std::string& message);