#pragma once

#include <boost/shared_ptr.hpp>

class IHandler
{
public:
    virtual void OnRender() = 0;
    virtual void OnKeyboard(unsigned char key, int x, int y) = 0;
};

typedef boost::shared_ptr<IHandler> IHandlerPtr;