#pragma once

#include "iBuffer.h"
#include <glad/glad.h>

class TextureBuffer2D : public iBuffer
{
public:
    TextureBuffer2D(GLenum textureId);
    ~TextureBuffer2D();

    virtual void bind() override;
    virtual void unBind() override;
    virtual bool getBindingState() const override;

    void write(
            const int width,
            const int height,
            const GLenum format,
            const void *const dataPtr
    );

private:
    void setBindingState(bool state);

private:
    const GLuint m_id;
    bool m_bindingState;
    GLenum m_textureId;

};
