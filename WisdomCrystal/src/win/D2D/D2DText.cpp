// D2DText.cpp

#include "D2DText.h"


D2DText::D2DText() : mGraphicsDevice(nullptr),
                     mTextFormat(nullptr),
                     mBrush(nullptr),
                     mFontFamilyName(TEXT("ÉÅÉCÉäÉI")),
                     mFontSize(12.0f),
                     mFontWeight(DWRITE_FONT_WEIGHT_NORMAL),
                     mFontStyle(DWRITE_FONT_STYLE_NORMAL),
                     mFontStretch(DWRITE_FONT_STRETCH_NORMAL)
{
    // empty
}


D2DText::~D2DText() {
    // empty
}


bool D2DText::Init(GraphicsDevice* graphicsDevice) {
    mGraphicsDevice = graphicsDevice;

    if (SetColor(D2D1::ColorF(0x000000)) == false) {
        return false;
    }

    if (CreateTextFormat() == false) {
        return false;
    }

    return true;
}


void D2DText::Draw(const std::basic_string<TCHAR>& string, const D2D1_RECT_F& layoutRect) {
    mGraphicsDevice->GetRenderTarget()->DrawText(string.c_str(),
                                                 string.size(),
                                                 mTextFormat,
                                                 layoutRect,
                                                 mBrush);
}


void D2DText::Draw(const std::basic_string<TCHAR>& string, const RECT& rect) {
    D2D1_RECT_F targetRect = D2D1::RectF(static_cast<float>(rect.left),
                                         static_cast<float>(rect.top),
                                         static_cast<float>(rect.right),
                                         static_cast<float>(rect.bottom));

    mGraphicsDevice->GetRenderTarget()->DrawText(string.c_str(),
                                                 string.size(),
                                                 mTextFormat,
                                                 targetRect,
                                                 mBrush);
}



bool D2DText::CreateTextFormat() {
    HRESULT hr = mGraphicsDevice->GetWriteFactory()->CreateTextFormat(mFontFamilyName.c_str(),
                                                                      nullptr,
                                                                      mFontWeight,
                                                                      mFontStyle,
                                                                      mFontStretch,
                                                                      mFontSize,
                                                                      TEXT("ja-jp"),
                                                                      &mTextFormat);

    if (SUCCEEDED(hr) == false) {
        return false;
    }

    return true;
}



bool D2DText::SetColor(const D2D1_COLOR_F& color) {
    HRESULT hr = mGraphicsDevice->GetRenderTarget()->CreateSolidColorBrush(color, &mBrush);
    if (SUCCEEDED(hr) == false) {
        return false;
    }

    return true;
}


bool D2DText::SetFontSize(const float fontSize) {
    if (fontSize <= 0) {
        return false;
    }

    mFontSize = fontSize;
    if (CreateTextFormat() == false) {
        return false;
    }

    return true;
}


bool D2DText::SetFontWeight(const DWRITE_FONT_WEIGHT& fontWeight) {
    mFontWeight = fontWeight;
    if (CreateTextFormat() == false) {
        return false;
    }

    return true;
}


bool D2DText::SetFontStyle(const DWRITE_FONT_STYLE& fontStyle) {
    mFontStyle = fontStyle;
    if (CreateTextFormat() == false) {
        return false;
    }

    return true;
}


bool D2DText::SetFontStretch(const DWRITE_FONT_STRETCH& fontStretch) {
    mFontStretch = fontStretch;
    if (CreateTextFormat() == false) {
        return false;
    }

    return true;
}
