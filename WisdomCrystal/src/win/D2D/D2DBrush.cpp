// D2DBrush.cpp

#include "D2DBrush.h"


D2DBrush::D2DBrush() : mRenderTarget(nullptr), mGradientStops(nullptr), mBrush(nullptr) {
    // empty
}


D2DBrush::~D2DBrush() {
    // empty
}


void D2DBrush::Init(GraphicsDevice* graphicsDevice) {
    mRenderTarget = graphicsDevice->GetRenderTarget();
}


bool D2DBrush::CreateLinearGradientBrush() {
    D2D1_GRADIENT_STOP gradientStops[3];

    gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Red, 1);
    gradientStops[0].position = 0.0f;
    gradientStops[1].color = D2D1::ColorF(D2D1::ColorF(0xffc9cc0));
    gradientStops[1].position = 0.5f;
    gradientStops[2].color = D2D1::ColorF(D2D1::ColorF::Red, 1);
    gradientStops[2].position = 1.0f;

    HRESULT hr = mRenderTarget->CreateGradientStopCollection(gradientStops,
                                                             3,
                                                             D2D1_GAMMA_2_2,
                                                             D2D1_EXTEND_MODE_CLAMP,
                                                             &mGradientStops);
    if (FAILED(hr)) {
        return false;
    }

    hr = mRenderTarget->CreateLinearGradientBrush(
        D2D1::LinearGradientBrushProperties(
            D2D1::Point2F(0, 75),
            D2D1::Point2F(250, 75)),
        mGradientStops,
        &mBrush);

    if (FAILED(hr)) {
        return false;
    }

    return true;
}


void D2DBrush::Update() {

    static int x = -250;
    x += 5;
    if (x >= 400) { x = -400; }

    mBrush->Release();
    mRenderTarget->CreateLinearGradientBrush(
        D2D1::LinearGradientBrushProperties(
            D2D1::Point2F((float)x, 75),
            D2D1::Point2F(150, 75)),
        mGradientStops,
        &mBrush);
}
