// GraphicsDevice.cpp

#include "win/GraphicsDevice.h"


GraphicsDevice::GraphicsDevice() : mD3DCore(), mD2DCore(), mWICCore() {
    // empty
}


GraphicsDevice::~GraphicsDevice() {
    // empty
}


bool GraphicsDevice::Init(const HWND& hWnd, int clientWidth, int clientHeight) {
    
    // Direct3D 10.1の初期化
    if (mD3DCore.Init(hWnd, clientWidth, clientHeight) == false) {
        MessageBox(nullptr, TEXT("Direct3D の初期化に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // Direct2D の初期化
    if (mD2DCore.Init(hWnd, mD3DCore.GetSwapChain()) == false) {
        MessageBox(nullptr, TEXT("Direct2D の初期化に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // WIC の初期化
    if (mWICCore.Init(mD2DCore.GetRenderTarget()) == false) {
        MessageBox(nullptr, TEXT("WIC の初期化に失敗しました"), TEXT("ERROR"), MB_OK);
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


void GraphicsDevice::SetFullScreenState(bool isFullscreen) {
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
