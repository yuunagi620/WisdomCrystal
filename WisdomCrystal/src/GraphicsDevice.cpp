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
    
    // Direct3D 10.1の初期化
    if (mD3DCore.Init(hWnd, screenWidth, screenHeight) == false) {
        MessageBox(nullptr, TEXT("Can not initialize Direct3D."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // Direct2D の初期化
    if (mD2DCore.Init(hWnd, mD3DCore.GetSwapChain()) == false) {
        MessageBox(nullptr, TEXT("Can not initialize Direct2D."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // WIC の初期化
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


COMPtr<ID2D1Bitmap> GraphicsDevice::CreateBitmapFromFile(LPCTSTR imageFilePath) {
    return mWICCore.CreateBitmapFromFile(imageFilePath);
}


COMPtr<ID2D1Bitmap> GraphicsDevice::CreateBitmapFromResource(LPCTSTR resourceName, LPCTSTR resourceType) {
    return mWICCore.CreateBitmapFromResource(resourceName, resourceType);
}


void GraphicsDevice::DrawBitmap(ID2D1Bitmap* bitmap,
                                const D2D1_RECT_F& destinationRectangle,
                                const float opacity,
                                const D2D1_RECT_F& sourceRectangle) {

    mD2DCore.DrawBitmap(bitmap, destinationRectangle, opacity, sourceRectangle);
}
