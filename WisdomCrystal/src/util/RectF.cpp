// RectF.cpp

#include "RectF.h"


namespace Util {

RectF::RectF() : x(0.f), y(0.f), width(0.f), height(0.f)
{
    // empty
}


RectF::RectF(float initX, float initY, float initWidth, float initHeight)
    : x(initX), y(initY), width(initWidth), height(initHeight)
{
    // empty
}



RectF::~RectF() {
    // empty
}

} // namespace Util
