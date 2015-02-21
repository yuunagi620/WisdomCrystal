// RectangleF.cpp

#include "RectangleF.h"


namespace Util {

RectangleF::RectangleF() : x(0.f), y(0.f), width(0.f), height(0.f)
{
    // empty
}


RectangleF::RectangleF(float initX, float initY, float initWidth, float initHeight)
    : x(initX), y(initY), width(initWidth), height(initHeight)
{
    // empty
}



RectangleF::~RectangleF() {
    // empty
}

} // namespace Util
