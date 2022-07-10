#pragma once
#include <string.h>
#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_TRACE 1
#define LOG_TRACE(val) if(LOG_LEVEL_TRACE) std::cout << "LOG_DEBUG::" << __FUNCTION__ << "()-> " << val <<  std::endl;
#define LOG_DEBUG(val) if(LOG_LEVEL_DEBUG) std::cout << "LOG_DEBUG::" << __FUNCTION__ << "()-> " << val <<  std::endl;
#define THROW_IF(val) if (val) std::cerr << "Failed to " << __FUNCTION__ << "()-> " << strerror(errno) << std::endl; return false; 
