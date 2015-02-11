// GraphicsDevice.cpp

#include "GraphicsDevice.h"


GraphicsDevice::GraphicsDevice() : mD3DCore(),
                                   mD2DCore(),
                                   mWICCore()
{
    // empty
}


GraphicsDevice::~GraphicsDevice() {
    // empty
}


bool GraphicsDevice::Init(const HWND& hWnd, const int screenWidth, const int screenHeight) {
    
    // Direct3D 10.1ÇÃèâä˙âª
    if (mD3DCore.Init(hWnd, screenWidth, screenHeight) == false) {
        MessageBox(nullptr, TEXT("Can not initialize Direct3D."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // Direct2D ÇÃèâä˙âª
    if (mD2DCore.Init(hWnd, mD3DCore.GetSwapChain()) == false) {
        MessageBox(nullptr, TEXT("Can not initialize Direct2D."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // WIC ÇÃèâä˙âª
    if (mWICCore.Init(mD2DCore.GetRenderTarget()) == false) {
        MessageBox(nullptr, TEXT("Can not initialize WIC."), TEXT("ERROR"), MB_OK);
        return false;
    }

    return true;
}


void GraphicsDevice::BeginDraw() {
    mD2DCore.BeginDraw();
}


HRESULT GraphicsDevice::EndDraw() {
    return mD2DCore.EndDraw();
}


void GraphicsDevice::Present() {
    mD3DCore.Present();
}


void GraphicsDevice::SetFullScreenState(const bool isFullscreen) {
    mD3DCore.SetFullscreenState(isFullscreen);
}


void GraphicsDevice::ClearScreen(const D2D1_COLOR_F& fillColor) {
    mD2DCore.ClearScreen(fillColor);
}


ID2D1Bitmap* GraphicsDevice::CreateD2DBitmap(LPCTSTR imageFilePath) {
    return mWICCore.CreateD2DBitmapFromFile(imageFilePath);
}


ID2D1Bitmap* GraphicsDevice::CreateD2DBitmap(LPCTSTR resourceName, LPCTSTR resourceType) {
    return mWICCore.CreateD2DBitmapFromResource(resourceName, resourceType);
}


void GraphicsDevice::DrawBitmap(ID2D1Bitmap* bitmap,
                                const D2D1_RECT_F& destinationRectangle,
                                const float opacity,
                                const D2D1_RECT_F& sourceRectangle) {

    mD2DCore.DrawBitmap(bitmap, destinationRectangle, opacity, sourceRectangle);
}


void GraphicsDevice::ResetTransform() {
    mD2DCore.ResetTransform();
}


void GraphicsDevice::FlipHorizontal(const float centerX, const float centerY) {
    mD2DCore.FlipHorizontal(centerX, centerY);
}


void GraphicsDevice::FlipVertical(const float centerX, const float centerY) {
    mD2DCore.FlipVertical(centerX, centerY);
}


void GraphicsDevice::RotateTransform(const float centerX, const float centerY, const float angle) {
    mD2DCore.RotateTransform(centerX, centerY, angle);
}
