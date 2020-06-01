#pragma once

#define ASSERT(x)	if(!(x)) __builtin_trap();
#define GLCALL(x)	GLClearError();\
					x;\
					ASSERT(GLErrorLog(#x, __FILE__, __LINE__))

void GLClearError(void);
bool GLErrorLog(const char * const functionName, const char* const file, int line);
