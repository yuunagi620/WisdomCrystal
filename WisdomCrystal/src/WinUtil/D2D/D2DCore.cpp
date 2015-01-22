// D2DCore.cpp

#pragma comment(lib, "DWrite.lib")

// Includes
#include "D2DCore.h"
#include "Winutil/SafeRelease.h"


// Static member variables
ID2D1RenderTarget *D2DCore::mRenderTarget = nullptr;


D2DCore::D2DCore() : mD2DFactory(nullptr),
                     mWriteFactory(nullptr)
{
    // empty
}


D2DCore::~D2DCore() {
    Cleanup();
}


bool D2DCore::Init(const HWND hWnd, IDXGISwapChain* swapChain) {

    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mD2DFactory);
    if (FAILED(hr)) {
        return false; // D2D�t�@�N�g�������Ɏ��s
    }

    if (createWriteFactory() == false) {
        return false;
    }


    IDXGISurface *backBuffer;
    hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    if (FAILED(hr)) {
        return false; // backBuffe�̊m�ۂɎ��s
    }

    // �f�X�N�g�b�v��DPI�擾
    float dpiX, dpiY;
    mD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

    // RenderTarget �v���p�e�B�̐ݒ�
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
            dpiX,
            dpiY);

    // Direct2D�p�̃����_�[�^�[�Q�b�g�쐬
    hr = mD2DFactory->CreateDxgiSurfaceRenderTarget(backBuffer,
                                                    &props,
                                                    &mRenderTarget);

    if (FAILED(hr)) {
        return false; // �����_�[�^�[�Q�b�g�̐����Ɏ��s
    }

    SafeRelease(&backBuffer); // �ȍ~�A�o�b�N�o�b�t�@�͎g��Ȃ��̂ŉ��

    return true;
}


void D2DCore::Cleanup() {
    SafeRelease(&mD2DFactory);
    SafeRelease(&mWriteFactory);
    SafeRelease(&mRenderTarget);
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


void D2DCore::DrawBitmap(ID2D1Bitmap* bitmap,
                         const D2D1_RECT_F& destinationRectangle,
                         const float opacity,
                         const D2D1_RECT_F& sourceRectangle) {

    mRenderTarget->DrawBitmap(bitmap,
                              destinationRectangle,
                              opacity,
                              D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
                              sourceRectangle);
}


void D2DCore::ResetTransform() {
    mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}


void D2DCore::FlipHorizontal(const float centerX, const float centerY) {
    mRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(-1, 1, D2D1::Point2F(centerX, centerY)));
}


void D2DCore::FlipVertical(const float centerX, const float centerY) {
    mRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(1, -1, D2D1::Point2F(centerX, centerY)));
}


void D2DCore::RotateTransform(const float centerX, const float centerY, const float angle) {
    mRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(centerX, centerY)));
}


bool D2DCore::createWriteFactory() {
    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                                     __uuidof(mWriteFactory),
                                     reinterpret_cast<IUnknown **>(&mWriteFactory));

    if (SUCCEEDED(hr) == false) {
        return false; // IDWriteFactory �̍쐬�Ɏ��s
    }

    return true;
}
