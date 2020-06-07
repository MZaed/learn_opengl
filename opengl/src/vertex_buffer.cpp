#include "vertex_buffer.h"
#include "gl_error_check.h"

VertexBuffer::VertexBuffer()
: m_id(0U),
  m_bindingState(false)
{
    GLCALL(glGenBuffers(1, const_cast<GLuint *>(&m_id)));
}

VertexBuffer::~VertexBuffer() {
    GLCALL(glDeleteBuffers(1, &m_id));
}

void VertexBuffer::bind() {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
    setBindingState(true);

}

void VertexBuffer::unBind() {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    setBindingState(false);
}

bool VertexBuffer::getBindingState() const {
    return m_bindingState;
}

void VertexBuffer::write(const void* const dataPtr, const unsigned int sizeInBytes) {
    bind();
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeInBytes, dataPtr, GL_STATIC_DRAW));
}

void VertexBuffer::setBindingState(bool state) {
    m_bindingState = state;
}
