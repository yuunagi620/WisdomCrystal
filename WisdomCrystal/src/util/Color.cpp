// Color.cpp

#include "Color.h"


namespace Util {

Color::Color() : r(0), g(0), b(0), a(0)
{
    // empty
}


Color::Color(std::uint32_t rgb, float initA) {
    r = static_cast<float>((rgb & RED_MASK)   >> RED_SHIFT)   / 255.f;
    g = static_cast<float>((rgb & GREEN_MASK) >> GREEN_SHIFT) / 255.f;
    b = static_cast<float>((rgb & BLUE_MASK)  >> BLUE_SHIFT)  / 255.f;
    a = initA;
}


Color::Color(float initR, float initG, float initB, float initA)
    : r(initR), g(initG), b(initB), a(initA)
{
    // empty
}


Color::Color(std::uint8_t initR, std::uint8_t initG, std::uint8_t initB, std::uint8_t initA) {
    // empty
}



Color::~Color() {
    // empty
}

} // namespace Util
