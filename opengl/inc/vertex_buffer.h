#pragma once
#include "iBuffer.h"
#include <glad/glad.h>

class VertexBuffer : public iBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    virtual void bind() override;
    virtual void unBind() override;
    virtual bool getBindingState() const override;

    void write(const void* const dataPtr, const unsigned int sizeInBytes);

private:
    void setBindingState(bool state);

private:
    const GLuint m_id;
    bool m_bindingState;

};
