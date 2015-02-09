// D2DImage.cpp

// Includes
#include "D2DImage.h"


D2DImage::D2DImage() : mGraphicsDevice(nullptr),
                       mImage(nullptr),
                       mImageSize(),
                       mImageSrcRect()
{
    // empty
}


D2DImage::~D2DImage() {
    // empty
}


bool D2DImage::Init(GraphicsDevice* graphicsDevice, LPCTSTR imageFilePath) {
    mGraphicsDevice = graphicsDevice;
    mImage = mGraphicsDevice->CreateD2DBitmap(imageFilePath);
    if (mImage == nullptr) {
        return false;
    }
    mImageSize = mImage->GetPixelSize();

    mImageSrcRect = D2D1::RectF(0, 0, 
                                static_cast<float>(mImageSize.width),
                                static_cast<float>(mImageSize.height));
    return true;
}


void D2DImage::Draw(const int x, const int y, const float opacity) {
    D2D1_RECT_F targetRect = D2D1::RectF(static_cast<float>(x + mImageSrcRect.left),
                                         static_cast<float>(y + mImageSrcRect.top),
                                         static_cast<float>(x + mImageSrcRect.right),
                                         static_cast<float>(y + mImageSrcRect.bottom));

    mGraphicsDevice->DrawBitmap(mImage, targetRect, 1, mImageSrcRect);
}


void D2DImage::Draw(const RECT& rect, const float opacity) {
    D2D1_RECT_F targetRect = D2D1::RectF(static_cast<float>(rect.left),
                                         static_cast<float>(rect.top),
                                         static_cast<float>(rect.right),
                                         static_cast<float>(rect.bottom));

    mGraphicsDevice->DrawBitmap(mImage, targetRect, opacity, mImageSrcRect);
}


void D2DImage::SetImageSrcRect(const RECT& rect) {
    mImageSrcRect = D2D1::RectF(static_cast<float>(rect.left),
                                static_cast<float>(rect.top),
                                static_cast<float>(rect.right),
                                static_cast<float>(rect.bottom));
}