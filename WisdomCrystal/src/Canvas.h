// Canvas.h

#pragma once

#include "GraphicsDevice.h"
#include "win/D2D/D2DBrush.h"


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

    void FillRectangle(const int x, const int y, const int width, const int height, const D2DBrush& brush);
    void FillRectangle(const float x, const float y, const float width, const float height, const D2DBrush& brush);

private:
    COMPtr<ID2D1RenderTarget> mRenderTarget;
};
