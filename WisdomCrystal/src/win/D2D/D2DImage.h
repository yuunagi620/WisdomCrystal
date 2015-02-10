// D2DImage.h

#pragma once

#include <d2d1.h>

#include "GraphicsDevice.h"


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
    GraphicsDevice *mGraphicsDevice;

    ID2D1Bitmap *mImage;
    D2D1_SIZE_U mImageSize;
    D2D1_RECT_F mImageSrcRect;
};
