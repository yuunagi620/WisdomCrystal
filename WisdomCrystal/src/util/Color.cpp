// Color.cpp

#include "Color.h"

namespace Util {

Color::Color() : x(0), y(0), width(0), height(0)
{
    // empty
}


Color::Color(int initX, int initY, int initWidth, int initHeight)
    : x(initX), y(initY), width(initWidth), height(initHeight)
{
    // empty
}



Color::~Color() {
    // empty
}

} // namespace Util
