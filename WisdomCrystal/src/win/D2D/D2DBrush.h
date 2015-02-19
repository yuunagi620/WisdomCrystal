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

    inline COMPtr<ID2D1LinearGradientBrush> GetBrush() const {
        return mBrush;
    }

private:
    COMPtr<ID2D1RenderTarget> mRenderTarget;
    COMPtr<ID2D1GradientStopCollection> mGradientStops;
    COMPtr<ID2D1LinearGradientBrush> mBrush;
};
