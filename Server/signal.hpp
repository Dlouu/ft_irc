#pragma once

#include <csignal>
#include <iostream>

extern volatile sig_atomic_t sig_caught;
void catch_sig();
