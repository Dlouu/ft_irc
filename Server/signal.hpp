#pragma once

#include <csignal>
#include <iostream>
#include "Server.hpp"
#include "Command.hpp"

extern volatile sig_atomic_t sig_caught;
void catch_sig();
