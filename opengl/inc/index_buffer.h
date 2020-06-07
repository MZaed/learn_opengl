#pragma once
#include "iBuffer.h"
#include <glad/glad.h>

class IndexBuffer : public iBuffer
{

public:
    IndexBuffer();
    ~IndexBuffer();

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


