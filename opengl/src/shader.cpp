#include "shader.h"
#include "gl_error_check.h"

#include <fstream>
#include <sstream>
#include <malloc.h>

Shader::Shader(const std::string &filePath)
        : m_rendererID(0),
          m_filePath(filePath) {
    shaderProgramSourceType shaderSource = parseShader(m_filePath);

    m_rendererID = createShader(shaderSource.vertexSource, shaderSource.fragmentSource);
}

Shader::~Shader() {
    GLCALL(glDeleteProgram(m_rendererID));
}

void Shader::bind() const {
    GLCALL(glUseProgram(m_rendererID));
}

void Shader::unBind() const {
    GLCALL(glUseProgram(0));
}

void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    GLCALL(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform1i(const std::string &name, int value) {
    GLCALL(glUniform1i(getUniformLocation(name), value));
}

void Shader::SetUniformMat4fv(const std::string & name, const glm::mat4& mat4)
{
    GLCALL(glUniformMatrix4fv(getUniformLocation(name), 1, false, &mat4[0][0]));
}

int Shader::getUniformLocation(const std::string &uniformName) {
    GLCALL(int location = glGetUniformLocation(m_rendererID, uniformName.c_str()));

    if (-1 == location) {
        std::cout << "Warning:: uniform" << "doesn't exist" << std::endl;
    }

    return location;
}

shaderProgramSourceType Shader::parseShader(std::string &filePath) {
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(filePath);
    std::string line;
    std::stringstream ss[2];
    ShaderType shaderType = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("SHADER") != std::string::npos) {
            if (line.find("VERTEX") != std::string::npos) {
                shaderType = ShaderType::VERTEX;

            } else if (line.find("FRAGMENT") != std::string::npos) {
                shaderType = ShaderType::FRAGMENT;

            } else {
                //not expected to reach here
                shaderType = ShaderType::NONE;
            }

        } else {
            ss[(int) shaderType] << line << '\n';
        }
    }

    return {ss[(int) ShaderType::VERTEX].str(), ss[(int) ShaderType::FRAGMENT].str()};
}


unsigned int Shader::compileShader(const std::string &source, GLenum type) {
    GLuint shaderID = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);


    int result = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(sizeof(char) * length);
        glGetShaderInfoLog(shaderID, length, &length, message);
        std::cout << "Failed to compile shader" << std::endl;
        std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader"
                  << std::endl;
    }

    return shaderID;
}


unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    GLuint program = glCreateProgram();

    GLuint vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    GLuint fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
