#pragma once

#if defined(IS_MSVC)
    #define ASSERT(x)	if(!(x)) __debugbreak();
#elif defined(IS_GNU)
    #define ASSERT(x)    if(!(x)) __builtin_trap();
#else
    #error "Compiler not supported"
#endif

#define GLCALL(x)   GLClearError();\
                    x;\
                    ASSERT(GLErrorLog(#x, __FILE__, __LINE__))

void GLClearError(void);

bool GLErrorLog(const char *const functionName, const char *file, int line);

