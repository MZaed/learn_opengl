#pragma once

#include <iostream>

class iBuffer
{
public:
    virtual void bind() = 0;
    virtual void unBind() = 0;
    virtual bool getBindingState() const = 0;
};

