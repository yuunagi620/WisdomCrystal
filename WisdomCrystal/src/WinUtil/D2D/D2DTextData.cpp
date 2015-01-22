// D2DTextData.cpp

// Includes
#include "D2DTextData.h"
#include "Winutil/SafeRelease.h"


D2DTextData::D2DTextData() : mGraphicsDevice(nullptr),
                             mTextFormat(nullptr),
                             mBrush(nullptr),
                             mFontFamilyName(TEXT("ÉÅÉCÉäÉI")),
                             mFontSize(10.0f),
                             mFontWeight(DWRITE_FONT_WEIGHT_NORMAL),
                             mFontStyle(DWRITE_FONT_STYLE_NORMAL),
                             mFontStretch(DWRITE_FONT_STRETCH_NORMAL)
{
    // empty
}


D2DTextData::~D2DTextData() {
    Cleanup();
}


bool D2DTextData::Init(GraphicsDevice* graphicsDevice) {
    mGraphicsDevice = graphicsDevice;

    if (SetColor(D2D1::ColorF(0x000000)) == false) {
        return false;
    }

    if (CreateTextFormat() == false) {
        return false;
    }

    return true;
}


void D2DTextData::Cleanup() {
    SafeRelease(&mBrush);
}


void D2DTextData::DrawText(const std::basic_string<TCHAR>& string, const D2D1_RECT_F& layoutRect) {
    mGraphicsDevice->GetRenderTarget()->DrawText(string.c_str(),
                                                 string.size(),
                                                 mTextFormat,
                                                 layoutRect,
                                                 mBrush);
}


bool D2DTextData::CreateTextFormat() {
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



bool D2DTextData::SetColor(const D2D1_COLOR_F& color) {        
    HRESULT hr = mGraphicsDevice->GetRenderTarget()->CreateSolidColorBrush(color, &mBrush);
    if (SUCCEEDED(hr) == false) {
        return false;
    }

    return true;
}


bool D2DTextData::SetFontSize(const float fontSize) {
    if (fontSize <= 0) {
        return false;
    }

    mFontSize = fontSize;
    if (CreateTextFormat() == false) {
        return false;
    }

    return true;
}


bool D2DTextData::SetFontWeight(const DWRITE_FONT_WEIGHT& fontWeight) {
    mFontWeight = fontWeight;
    if (CreateTextFormat() == false) {
        return false;
    }

    return true;
}


bool D2DTextData::SetFontStyle(const DWRITE_FONT_STYLE& fontStyle) {
    mFontStyle = fontStyle;
    if (CreateTextFormat() == false) {
        return false;
    }

    return true;
}


bool D2DTextData::SetFontStretch(const DWRITE_FONT_STRETCH& fontStretch) {
    mFontStretch = fontStretch;
    if (CreateTextFormat() == false) {
        return false;
    }

    return true;
}
