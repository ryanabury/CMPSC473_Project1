#pragma once

#include "ThreadTests.h"

void protected_print4(std::string str);

// Relies on mB then mA
void fun4A(int tid);

// Relies on mA then mB
void fun4B(int tid);