#pragma once

//#define DEBUG
#ifdef DEBUG
#define LOGHEX(name, val) std::cout << name << ": " << std::hex << val << std::endl;
#else
#define LOGHEX(name, val)
#endif