#include "index_buffer.h"
#include "gl_error_check.h"

IndexBuffer::IndexBuffer()
:   m_id(0),
    m_bindingState(false)
{
    GLCALL(glGenBuffers(1, const_cast<GLuint*>(&m_id)));
}

IndexBuffer::~IndexBuffer() {
    GLCALL(glDeleteBuffers(1, &m_id));
}

void IndexBuffer::bind() {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
    setBindingState(true);
}

void IndexBuffer::unBind() {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    setBindingState(false);
}

bool IndexBuffer::getBindingState() const {
    return m_bindingState;
}

void IndexBuffer::write(const void *const dataPtr, const unsigned int sizeInBytes) {
    bind();
    GLCALL(glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeInBytes, dataPtr, GL_STATIC_DRAW));
}

void IndexBuffer::setBindingState(bool state) {
    m_bindingState = state;

}
