#include "vertex_array.h"

#include <glad/glad.h>
#include "gl_error_check.h"

void VertexArray::bind() {
    GLCALL(glBindVertexArray(m_id));
    setBindingState(true);
}

void VertexArray::unBind() {
    GLCALL(glBindVertexArray(0));
    setBindingState(false);
}


bool VertexArray::getBindingState() const {
    return m_bindingState;
}

void VertexArray::setBindingState(bool state) {
    m_bindingState = state;
}

VertexArray::VertexArray()
: m_id(0U),
  m_bindingState(false)
{
    GLCALL(glGenVertexArrays(1, const_cast<GLuint *>(&m_id)));
}

VertexArray::~VertexArray() {
    GLCALL(glDeleteVertexArrays(1, &m_id));
}
