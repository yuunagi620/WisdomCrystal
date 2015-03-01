// D2DText.cpp

#include "D2DText.h"


D2DText::D2DText() : mRenderTarget(nullptr),
                     mWriteFactory(nullptr),
                     mTextFormat(nullptr),
                     mBrush(nullptr),
                     mFontFamilyName(TEXT("ƒƒCƒŠƒI")),
                     mFontSize(12.0f),
                     mFontWeight(DWRITE_FONT_WEIGHT_NORMAL),
                     mFontStyle(DWRITE_FONT_STYLE_NORMAL),
                     mFontStretch(DWRITE_FONT_STRETCH_NORMAL) {
    // empty
}


D2DText::~D2DText() {
    // empty
}


bool D2DText::Init(GraphicsDevice* graphicsDevice) {
    mRenderTarget = graphicsDevice->GetRenderTarget();
    mWriteFactory = graphicsDevice->GetWriteFactory();

    if (SetColor(D2D1::ColorF(0x000000)) == false) {
        return false;
    }

    if (CreateTextFormat() == false) {
        return false;
    }

    return true;
}


void D2DText::Draw(const std::basic_string<TCHAR>& string,
                   const int x, const int y, const int width, const int height) {

    RECT rect = {x, y, width, height};
    Draw(string, rect);
}


void D2DText::Draw(const std::basic_string<TCHAR>& string, const RECT& layoutRect) {
    mRenderTarget->DrawText(string.c_str(),
                            string.size(),
                            mTextFormat,
                            D2D1::RectF(static_cast<float>(layoutRect.left),
                                        static_cast<float>(layoutRect.top),
                                        static_cast<float>(layoutRect.right),
                                        static_cast<float>(layoutRect.bottom)),
                            mBrush);
}



bool D2DText::CreateTextFormat() {
    HRESULT hr = mWriteFactory->CreateTextFormat(mFontFamilyName.c_str(),
                                                 nullptr,
                                                 mFontWeight,
                                                 mFontStyle,
                                                 mFontStretch,
                                                 mFontSize,
                                                 TEXT("ja-jp"),
                                                 &mTextFormat);

    if (FAILED(hr)) {
        return false;
    }

    return true;
}


bool D2DText::SetColor(const D2D1_COLOR_F& color) {
    mBrush.Release();
    HRESULT hr = mRenderTarget->CreateSolidColorBrush(color, &mBrush);
    if (FAILED(hr)) {
        return false;
    }

    return true;
}


bool D2DText::SetFontFamilyName(const std::basic_string<TCHAR>& fontFamilyName) {
    mFontFamilyName = fontFamilyName;
    return CreateTextFormat();
}


bool D2DText::SetFontSize(const float fontSize) {
    if (fontSize <= 0) {
        return false;
    }

    mFontSize = fontSize;
    return CreateTextFormat();
}


bool D2DText::SetFontWeight(const DWRITE_FONT_WEIGHT& fontWeight) {
    mFontWeight = fontWeight;
    return CreateTextFormat();
}


bool D2DText::SetFontStyle(const DWRITE_FONT_STYLE& fontStyle) {
    mFontStyle = fontStyle;
    return CreateTextFormat();
}


bool D2DText::SetFontStretch(const DWRITE_FONT_STRETCH& fontStretch) {
    mFontStretch = fontStretch;
    return CreateTextFormat();
}
