// Canvas.h

#pragma once

#include "win/GraphicsDevice.h"
#include "win/D2D/D2DBrush.h"


class Canvas {

public:
    Canvas();

    virtual ~Canvas();

    void Init(GraphicsDevice *mGraphicsDevice);

    void Clear(D2D1_COLOR_F& fillColor);

    void ResetTransform();

    void FlipHorizontal(float centerX, float centerY);

    void FlipVertical(float centerX, float centerY);

    void RotateTransform(float centerX, float centerY, float angle);

    void FillRectangle(int x, int y, int width, int height, const D2DBrush& brush);
    void FillRectangle(float x, float y, float width, float height, const D2DBrush& brush);

private:
    COMPtr<ID2D1RenderTarget> mRenderTarget;
};
