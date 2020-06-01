#include "gl_error_check.h"
#include <glad/glad.h>
#include <iostream>

void GLClearError(void)
{
    while(glGetError() != GL_NO_ERROR){
        //do nothing
    }
}

bool GLErrorLog(const char * const functionName, const char * const file, int line)
{
    while(GLenum error = glGetError()){
        std::cout << "GL Error: [" << error << "]" << std::endl;
        std::cout << "Funcation Name: " << functionName << std::endl;
        std::cout << "File Name: " << file << " at Line no. '" << line << "'" << std::endl;
        return false;
    }

    return true;
}