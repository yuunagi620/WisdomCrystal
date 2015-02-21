// Color.h

#pragma once

#pragma warning (disable: 4005) // C4005 警告無視
#include <cstdint>
#pragma warning (default: 4005) // C4005 警告解除


namespace Util {

class Color {

public:
    Color();
    Color(float red, float green, float blue, float alpha = 1.0f);
    Color(std::uint32_t rgb, float alpha = 1.0f);
    
    virtual ~Color();

    // RGB 形式に変換して返します
    std::uint32_t ToRGB() const;

    float GetRed()   const { return mRed;   }
    float GetGreen() const { return mGreen; }
    float GetBlue()  const { return mBlue;  }
    float GetAlpha() const { return mAlpha; }

    void SetRed  (float red)   { mRed   = red;   }
    void SetGreen(float green) { mGreen = green; }
    void SetBlue (float blue)  { mBlue  = blue;  }
    void SetAlpha(float alpha) { mAlpha = alpha; }

private:
    static const UINT32 RED_SHIFT   = 16; // 赤のビットシフト数
    static const UINT32 GREEN_SHIFT = 8;  // 緑のビットシフト数
    static const UINT32 BLUE_SHIFT  = 0;  // 青のビットシフト数

    static const UINT32 RED_MASK   = 0xff << RED_SHIFT;   // 赤のビットマスク
    static const UINT32 GREEN_MASK = 0xff << GREEN_SHIFT; // 緑のビットマスク
    static const UINT32 BLUE_MASK  = 0xff << BLUE_SHIFT;  // 青のビットマスク

    float mRed, mGreen, mBlue, mAlpha;
};

} // namespace Util
