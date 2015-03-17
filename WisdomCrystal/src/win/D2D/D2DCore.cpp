// D2DCore.cpp

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "DWrite.lib")

#include "D2DCore.h"


D2DCore::D2DCore() : mD2DFactory(nullptr), mWriteFactory(nullptr), mRenderTarget(nullptr) {    
    // empty
}


D2DCore::~D2DCore() {
    // empty
}


bool D2DCore::Init(const HWND& hWnd, COMPtr<IDXGISwapChain> swapChain) {

    // D2DFactory の作成
    if (createD2DFactory() == false) {
        return false;
    }

    // WriteFactory の作成
    if (createWriteFactory() == false) {
        return false;
    }

    // BackBuffer の作成
    COMPtr<IDXGISurface> backBuffer(nullptr);
    HRESULT hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    if (FAILED(hr)) {
        return false;
    }

    // デスクトップのDPI取得
    float dpiX = 0;
    float dpiY = 0;
    mD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

    // RenderTarget プロパティの設定
    D2D1_RENDER_TARGET_PROPERTIES props =
        D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
                                     D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
                                     dpiX,
                                     dpiY);

    // Direct2D用のレンダーターゲット作成
    hr = mD2DFactory->CreateDxgiSurfaceRenderTarget(backBuffer,
                                                    &props,
                                                    &mRenderTarget);
    if (FAILED(hr)) {
        return false;
    }

    return true;
}


void D2DCore::BeginDraw() {
    mRenderTarget->BeginDraw();
}


HRESULT D2DCore::EndDraw() {
    return mRenderTarget->EndDraw();
}


void D2DCore::ClearScreen(const D2D1_COLOR_F& fillColor) {
    mRenderTarget->Clear(fillColor);
}


bool D2DCore::createD2DFactory() {
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mD2DFactory);
    if (FAILED(hr)) {
        return false;
    }

    return true;
}


bool D2DCore::createWriteFactory() {
    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                                     __uuidof(mWriteFactory),
                                     reinterpret_cast<IUnknown **>(&mWriteFactory));
    if (FAILED(hr)) {
        return false;
    }

    return true;
}

