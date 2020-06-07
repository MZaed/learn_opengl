#include "texture_buffer2D.h"
#include "gl_error_check.h"
#include <glad/glad.h>


TextureBuffer2D::TextureBuffer2D(GLenum textureId)
:   m_id(0),
    m_bindingState(false),
    m_textureId(textureId)
{
    GLCALL(glGenTextures(1, const_cast<GLuint *>(&m_id)));
}

TextureBuffer2D::~TextureBuffer2D() {
    GLCALL(glDeleteTextures(1, &m_id));
}

void TextureBuffer2D::bind() {
    GLCALL(glActiveTexture(m_textureId));
    GLCALL(glBindTexture(GL_TEXTURE_2D, m_id));
    setBindingState(true);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void TextureBuffer2D::unBind() {

    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
    setBindingState(false);
}

bool TextureBuffer2D::getBindingState() const {
    return m_bindingState;
}

void TextureBuffer2D::write(
        const int width,
        const int height,
        const GLenum format,
        const void *const dataPtr
) {

    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, dataPtr));
    GLCALL(glGenerateMipmap(GL_TEXTURE_2D));

}

void TextureBuffer2D::setBindingState(bool state) {
    m_bindingState = state;

}
