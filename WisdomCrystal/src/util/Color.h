// Color.h

#pragma once

#pragma warning (disable: 4005) // C4005 �x������
#include <cstdint>
#pragma warning (default: 4005) // C4005 �x������


namespace Util {

class Color {

public:
    Color();
    Color(float red, float green, float blue, float alpha = 1.0f);
    Color(std::uint32_t rgb, float alpha = 1.0f);
    
    virtual ~Color();

    // RGB �`���ɕϊ����ĕԂ��܂�
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
    static const UINT32 RED_SHIFT   = 16; // �Ԃ̃r�b�g�V�t�g��
    static const UINT32 GREEN_SHIFT = 8;  // �΂̃r�b�g�V�t�g��
    static const UINT32 BLUE_SHIFT  = 0;  // �̃r�b�g�V�t�g��

    static const UINT32 RED_MASK   = 0xff << RED_SHIFT;   // �Ԃ̃r�b�g�}�X�N
    static const UINT32 GREEN_MASK = 0xff << GREEN_SHIFT; // �΂̃r�b�g�}�X�N
    static const UINT32 BLUE_MASK  = 0xff << BLUE_SHIFT;  // �̃r�b�g�}�X�N

    float mRed, mGreen, mBlue, mAlpha;
};

} // namespace Util
