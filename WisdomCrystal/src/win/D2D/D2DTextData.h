// D2DTextData.h

#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <Dwrite.h>
#include <string>
#include <memory>

#include "GraphicsDevice.h"
#include "win/COM/Deleter.h"


class D2DTextData {

public:
    D2DTextData();

    virtual ~D2DTextData();

    bool Init(GraphicsDevice *mGraphicsDevice);

    void Draw(const std::basic_string<TCHAR>& string, const D2D1_RECT_F& layoutRect);

    bool CreateTextFormat();

    bool SetColor(const D2D1_COLOR_F& color);

    bool SetFontSize(const float fontSize);

    bool SetFontWeight(const DWRITE_FONT_WEIGHT& fontWeight);

    bool SetFontStyle(const DWRITE_FONT_STYLE& fontStyle);

    bool SetFontStretch(const DWRITE_FONT_STRETCH& fontStretch);

private:
    GraphicsDevice    *mGraphicsDevice;
    IDWriteTextFormat *mTextFormat;

    std::unique_ptr<ID2D1SolidColorBrush, Deleter<ID2D1SolidColorBrush>> mBrush;

    std::basic_string<TCHAR> mFontFamilyName;
    float mFontSize;

    DWRITE_FONT_WEIGHT  mFontWeight;
    DWRITE_FONT_STYLE   mFontStyle;
    DWRITE_FONT_STRETCH mFontStretch;
};
