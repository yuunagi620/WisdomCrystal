// Color.h

#pragma once

#include <cstdint>


namespace Util {

class Color {

public:
    float r, g, b, a;

public:
    Color();
    Color(std::uint32_t rgb, float initA);
    Color(float initR, float initG, float initB, float initA);
    Color(std::uint8_t initR, std::uint8_t initG, std::uint8_t initB, std::uint8_t initA);
    
    virtual ~Color();

    inline std::uint32_t ToR8G8B8() const {
        const std::uint32_t r_ = static_cast<std::uint32_t>(r * 255) << 16;
        const std::uint32_t g_ = static_cast<std::uint32_t>(g * 255) <<  8;
        const std::uint32_t b_ = static_cast<std::uint32_t>(b * 255) <<  0;
        return (r_ | g_ | b_);
    }
private:
    static const UINT32 RED_SHIFT   = 16;
    static const UINT32 GREEN_SHIFT = 8;
    static const UINT32 BLUE_SHIFT  = 0;    

    static const UINT32 RED_MASK   = 0xff << RED_SHIFT;
    static const UINT32 GREEN_MASK = 0xff << GREEN_SHIFT;
    static const UINT32 BLUE_MASK  = 0xff << BLUE_SHIFT;   
};


} // namespace Util
