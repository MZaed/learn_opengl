#ifndef LEARN_OPENGL_VERTEX_ATTRIBUTE_H
#define LEARN_OPENGL_VERTEX_ATTRIBUTE_H

#include "iBuffer.h"
#include <glad/glad.h>

class VertexArray : public iBuffer
{
public:
    VertexArray();
    virtual ~VertexArray();

    virtual void bind() override;
    virtual void unBind() override;
    virtual bool getBindingState() const override;

private:
    void setBindingState(bool state);

private:
    const GLuint m_id;
    bool m_bindingState;
};

#endif //LEARN_OPENGL_VERTEX_ATTRIBUTE_H
