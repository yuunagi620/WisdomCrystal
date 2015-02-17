// Canvas.h

#pragma once

#include "GraphicsDevice.h"


class Canvas {

public:
    Canvas();
    virtual ~Canvas();

    void Init(GraphicsDevice *mGraphicsDevice);

    void ResetTransform();

    void FlipHorizontal(const float centerX, const float centerY);

    void FlipVertical(const float centerX, const float centerY);

    void RotateTransform(const float centerX, const float centerY, const float angle);

private:
    COMPtr<ID2D1RenderTarget> mRenderTarget;
};
