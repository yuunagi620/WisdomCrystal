// D2DText.h

#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <Dwrite.h>
#include <string>

#include "GraphicsDevice.h"


class D2DText {

public:
    D2DText();

    virtual ~D2DText();

    bool Init(GraphicsDevice *mGraphicsDevice);

    void Draw(const std::basic_string<TCHAR>& string, const D2D1_RECT_F& layoutRect);

    void Draw(const std::basic_string<TCHAR>& string, const RECT& rect);

    bool CreateTextFormat();

    bool SetColor(const D2D1_COLOR_F& color);

    bool SetFontFamilyName(const std::basic_string<TCHAR>& fontFamilyName);

    bool SetFontSize(const float fontSize);

    bool SetFontWeight(const DWRITE_FONT_WEIGHT& fontWeight);

    bool SetFontStyle(const DWRITE_FONT_STYLE& fontStyle);

    bool SetFontStretch(const DWRITE_FONT_STRETCH& fontStretch);

private:
    COMPtr<ID2D1RenderTarget>    mRenderTarget;
    COMPtr<IDWriteFactory>       mWriteFactory;
    COMPtr<IDWriteTextFormat>    mTextFormat;
    COMPtr<ID2D1SolidColorBrush> mBrush;

    std::basic_string<TCHAR> mFontFamilyName;
    float mFontSize;

    DWRITE_FONT_WEIGHT  mFontWeight;
    DWRITE_FONT_STYLE   mFontStyle;
    DWRITE_FONT_STRETCH mFontStretch;
};
