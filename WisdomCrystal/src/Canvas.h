// Canvas.h

#pragma once

#include "GraphicsDevice.h"


class Canvas {

public:
    Canvas();
    virtual ~Canvas();

    void Init(GraphicsDevice *mGraphicsDevice);

    void Clear(const D2D1_COLOR_F& fillColor);

    void ResetTransform();

    void FlipHorizontal(const float centerX, const float centerY);

    void FlipVertical(const float centerX, const float centerY);

    void RotateTransform(const float centerX, const float centerY, const float angle);

private:
    COMPtr<ID2D1RenderTarget> mRenderTarget;
};
