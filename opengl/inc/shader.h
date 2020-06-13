#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct shaderProgramSourceType {
    std::string vertexSource;
    std::string fragmentSource;
};


class Shader {
public:
    Shader(const std::string &fileName);

    ~Shader();

    void bind() const;

    void unBind() const;


    // Set uniforms
    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

    void setUniform1i(const std::string &name, int value);

    void SetUniformMat4fv(const std::string & name, const glm::mat4& mat4);



private:

    unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);

    shaderProgramSourceType parseShader(std::string &filePath);

    unsigned int compileShader(const std::string &source, GLenum type);

    int getUniformLocation(const std::string &uniformName);

    unsigned int m_rendererID;
    std::string m_filePath;


};
