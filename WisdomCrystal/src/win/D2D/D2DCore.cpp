// D2DCore.cpp

#pragma comment(lib, "DWrite.lib")

// Includes
#include "D2DCore.h"
#include "win/util/SafeRelease.h"
#include "win/util/Deleter.h"


D2DCore::D2DCore() : mD2DFactory(nullptr),
                     mWriteFactory(nullptr),
                     mRenderTarget(nullptr)
{
    // empty
}


D2DCore::~D2DCore() {
    // empty
}


bool D2DCore::Init(const HWND hWnd, IDXGISwapChain* swapChain) {

    // Factory �̍쐬
    if (createFactory() == false) {
        return false;
    }

    // WriteFactory �̍쐬
    if (createWriteFactory() == false) {
        return false;
    }


    IDXGISurface *backBuffer;
    HRESULT hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
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
    ID2D1RenderTarget *renderTarget = nullptr;
    hr = mD2DFactory->CreateDxgiSurfaceRenderTarget(backBuffer,
                                                    &props,
                                                    &renderTarget);

    if (FAILED(hr)) {
        return false; // �����_�[�^�[�Q�b�g�̐����Ɏ��s
    }

    mRenderTarget.reset(renderTarget, Deleter<ID2D1RenderTarget>());

    SafeRelease(&backBuffer); // �ȍ~�A�o�b�N�o�b�t�@�͎g��Ȃ��̂ŉ��

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
    IDWriteFactory* writeFactory = nullptr;
    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                                     __uuidof(mWriteFactory),
                                     reinterpret_cast<IUnknown **>(&writeFactory));

    if (FAILED(hr)) {
        return false;
    }

    mWriteFactory.reset(writeFactory, Deleter<IDWriteFactory>());
    return true;
}


bool D2DCore::createFactory() {
    ID2D1Factory* factory = nullptr;
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
    if (FAILED(hr)) {
        return false;
    }

    mD2DFactory.reset(factory);
    return true;
}