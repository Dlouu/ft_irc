#pragma once

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include <cmath>
#include <map>
#include <vector>
#include <sstream>

std::vector<std::string> extractMessages(std::string& buffer);
