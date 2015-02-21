// Color.cpp

#include "Color.h"


namespace Util {

Color::Color() : mRed(0), mGreen(0), mBlue(0), mAlpha(0)
{
    // empty
}


Color::Color(float red, float green, float blue, float alpha)
    : mRed(red), mGreen(green), mBlue(blue), mAlpha(alpha)
{
    // empty
}


Color::Color(std::uint32_t rgb, float alpha) {
    mRed   = static_cast<float>((rgb & RED_MASK)   >> RED_SHIFT)   / 255.f;
    mGreen = static_cast<float>((rgb & GREEN_MASK) >> GREEN_SHIFT) / 255.f;
    mBlue  = static_cast<float>((rgb & BLUE_MASK)  >> BLUE_SHIFT)  / 255.f;
    mAlpha = alpha;
}


Color::~Color() {
    // empty
}


std::uint32_t Color::ToRGB() const {
    const std::uint32_t r = static_cast<std::uint32_t>(mRed   * 255) << 16;
    const std::uint32_t g = static_cast<std::uint32_t>(mGreen * 255) <<  8;
    const std::uint32_t b = static_cast<std::uint32_t>(mBlue  * 255) <<  0;
    return (r | g | b);
}

} // namespace Util
