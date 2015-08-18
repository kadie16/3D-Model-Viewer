#ifndef ERRORS
#define ERRORS
#pragma once
#include <string>

extern void fatalError(std::string errorString);
extern int CheckGLErrors();

#endif // ERRORS

