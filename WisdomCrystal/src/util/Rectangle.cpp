// Rectangle.cpp

#include "Rectangle.h"

namespace Util {

Rectangle::Rectangle() : x(0), y(0), width(0), height(0)
{
    // empty
}


Rectangle::Rectangle(int initX, int initY, int initWidth, int initHeight)
    : x(initX), y(initY), width(initWidth), height(initHeight)
{
    // empty
}



Rectangle::~Rectangle() {
    // empty
}

} // namespace Util
