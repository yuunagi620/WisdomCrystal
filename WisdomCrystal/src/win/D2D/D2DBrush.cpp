// D2DBrush.cpp

#include "D2DBrush.h"


D2DBrush::D2DBrush() : mRenderTarget(nullptr),
                       mGradientStops(nullptr),
                       mBrush(nullptr)
{
    // empty
}


D2DBrush::~D2DBrush() {
    // empty
}


void D2DBrush::Init(GraphicsDevice* graphicsDevice) {
    mRenderTarget = graphicsDevice->GetRenderTarget();
}


bool D2DBrush::CreateLinearGradientBrush() {
    D2D1_GRADIENT_STOP gradientStops[2];
    gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Yellow, 1);
    gradientStops[0].position = 0.0f;
    gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::ForestGreen, 1);
    gradientStops[1].position = 1.0f;

    HRESULT hr = mRenderTarget->CreateGradientStopCollection(gradientStops,
                                                             2,
                                                             D2D1_GAMMA_2_2,
                                                             D2D1_EXTEND_MODE_CLAMP,
                                                             &mGradientStops);
    if (FAILED(hr)) {
        return false;
    }

    hr = mRenderTarget->CreateLinearGradientBrush(
        D2D1::LinearGradientBrushProperties(
            D2D1::Point2F(0, 0),
            D2D1::Point2F(150, 150)),
        mGradientStops,
        &mBrush);

    if (FAILED(hr)) {
        return false;
    }
}


void D2DBrush::Update() {
    mRenderTarget->FillRectangle(D2D1::RectF(0.f, 0.f, 150.f, 150.f), mBrush);
}