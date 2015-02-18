// D2DBrush.h

#pragma once

#include "GraphicsDevice.h"


class D2DBrush {

public:
    D2DBrush();
    virtual ~D2DBrush();

    void Init(GraphicsDevice *mGraphicsDevice);

    bool CreateLinearGradientBrush();

    void Update();

private:
    COMPtr<ID2D1RenderTarget> mRenderTarget;
    COMPtr<ID2D1GradientStopCollection> mGradientStops;
    COMPtr<ID2D1LinearGradientBrush> mBrush;
};
