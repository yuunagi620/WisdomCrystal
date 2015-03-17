// D2DImage.h

#pragma once

#include <d2d1.h>

#include "win/GraphicsDevice.h"
#include "win/COM/COMPtr.h"


class D2DImage {

public:
    D2DImage();

    virtual ~D2DImage();

    bool Init(GraphicsDevice *mGraphicsDevice, LPCTSTR imageFilePath);
    bool Init(GraphicsDevice *mGraphicsDevice, LPCTSTR resourceName, LPCTSTR resourceType);

    void Draw(const int x, const int y, const float opacity = 1);
    void Draw(const RECT& rect, const float opacity = 1);

    void SetImageSrcRect(const RECT& rect);

private:
    COMPtr<ID2D1RenderTarget> mRenderTarget;
    COMPtr<ID2D1Bitmap>       mBitmap;

    D2D1_SIZE_U mImageSize;
    D2D1_RECT_F mImageSrcRect;
};
