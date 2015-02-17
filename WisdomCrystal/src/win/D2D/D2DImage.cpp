// D2DImage.cpp

#include "D2DImage.h"


D2DImage::D2DImage() : mRenderTarget(nullptr),
                       mBitmap(nullptr),
                       mImageSize(),
                       mImageSrcRect()
{
    // empty
}


D2DImage::~D2DImage() {
    // empty
}


bool D2DImage::Init(GraphicsDevice* graphicsDevice, LPCTSTR imageFilePath) {
    mRenderTarget = graphicsDevice->GetRenderTarget();

    mBitmap = graphicsDevice->CreateBitmapFromFile(imageFilePath);
    if (mBitmap == nullptr) {
        return false;
    }

    mImageSize = mBitmap->GetPixelSize();
    mImageSrcRect = D2D1::RectF(0, 0, 
                                static_cast<float>(mImageSize.width),
                                static_cast<float>(mImageSize.height));
    return true;
}


bool D2DImage::Init(GraphicsDevice* graphicsDevice, LPCTSTR resourceName, LPCTSTR resourceType) {
    mRenderTarget = graphicsDevice->GetRenderTarget();

    mBitmap = graphicsDevice->CreateBitmapFromResource(resourceName, resourceType);
    if (mBitmap == nullptr) {
        return false;
    }

    mImageSize = mBitmap->GetPixelSize();
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
    mRenderTarget->DrawBitmap(mBitmap,
                              targetRect,
                              opacity,
                              D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
                              mImageSrcRect);
}


void D2DImage::Draw(const RECT& rect, const float opacity) {
    D2D1_RECT_F targetRect = D2D1::RectF(static_cast<float>(rect.left),
                                         static_cast<float>(rect.top),
                                         static_cast<float>(rect.right),
                                         static_cast<float>(rect.bottom));
    mRenderTarget->DrawBitmap(mBitmap,
                              targetRect,
                              opacity,
                              D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
                              mImageSrcRect);
}


void D2DImage::SetImageSrcRect(const RECT& rect) {
    mImageSrcRect = D2D1::RectF(static_cast<float>(rect.left),
                                static_cast<float>(rect.top),
                                static_cast<float>(rect.right),
                                static_cast<float>(rect.bottom));
}