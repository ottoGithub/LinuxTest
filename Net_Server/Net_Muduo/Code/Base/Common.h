#pragma once

#include <cassert>
#include <iostream>
namespace xtProxima
{

#define NoCopy(classname) \
public:\
classname(const classname&) = delete; \
classname& operator=(const classname&) = delete;

#define Instance(classname) \
public:\
classname& Instance() { \
	static classname s; \
	return &s;  \
}

#ifdef _WIN32
#define FILENAME(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x
#elif defined(__GNUC__)
#define FILENAME(x) strrchr(x,'/')?strrchr(x,'/')+1:x
#endif

#define LOG_INFO(...) {\
	fprintf(stdout, "%s: Line %d;\t", FILENAME(__FILE__), __LINE__);\
	fprintf(stdout, __VA_ARGS__); \
	fprintf(stdout,"\n"); \
}

}
