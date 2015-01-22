// WICCore.cpp

// Includes
#include "WICCore.h"
#include "win/SafeRelease.h"


WICCore::WICCore() : mWICImagingFactory(nullptr),
                     mRenderTarget(nullptr)                 
{
    // empty
}


WICCore::~WICCore() {
    Cleanup();
}


bool WICCore::Init(ID2D1RenderTarget *renderTarget) {
    mRenderTarget = renderTarget;

    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory,
                                  nullptr,
                                  CLSCTX_INPROC_SERVER,
                                  IID_IWICImagingFactory,
                                  reinterpret_cast<void **>(&mWICImagingFactory));
    if (FAILED(hr)) {
        return false;
    }

    return true;
}


void WICCore::Cleanup() {
    SafeRelease(&mWICImagingFactory);
}


// �t�@�C���p�X���� ID2D1Bitmap ���쐬����֐�
ID2D1Bitmap *WICCore::CreateD2DBitmap(TCHAR *imageFilePath) {

    ID2D1Bitmap *d2dBitmap = nullptr;

    // IWICBitmapDecoder ���쐬
    IWICBitmapDecoder *decoder = nullptr;
    HRESULT hr = mWICImagingFactory->CreateDecoderFromFilename(imageFilePath,
                                                               nullptr,
                                                               GENERIC_READ,
                                                               WICDecodeMetadataCacheOnLoad,
                                                               &decoder);
    if (FAILED(hr)) {
        return nullptr; // IWICBitmapDecoder �̍쐬�Ɏ��s
    }

    // �C���[�W���� Frame ���擾���AIWICBitmapFrameDecode �I�u�W�F�N�g�Ɋi�[
    IWICBitmapFrameDecode *frame = nullptr;
    hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr)) {
        goto cleanup; // Frame �̊m�ۂɎ��s
    }

    // Direct2D �Ŏg�p�ł���`���ɕϊ�
    d2dBitmap = convertD2DBitmap(frame);

cleanup:
    SafeRelease(&frame);
    SafeRelease(&decoder);

    return d2dBitmap;
}


// Bitmap �� Direct2D �Ŏg�p�ł���`���ɕϊ�����֐�
ID2D1Bitmap *WICCore::convertD2DBitmap(IWICBitmapFrameDecode *frame) {

    ID2D1Bitmap *d2dBitmap = nullptr;

    // �C���[�W�̃s�N�Z���`���� 32bppPBGRA �ɕϊ�
    IWICFormatConverter *converter = nullptr;
    HRESULT hr = mWICImagingFactory->CreateFormatConverter(&converter);
    if (FAILED(hr)) {
        goto cleanup; // IWICFormatConverter �̍쐬�Ɏ��s
    }

    hr = converter->Initialize(frame,
                               GUID_WICPixelFormat32bppPBGRA,
                               WICBitmapDitherTypeNone,
                               nullptr,
                               0.0f,
                               WICBitmapPaletteTypeMedianCut);
    if (FAILED(hr)) {
        goto cleanup; // �C���[�W�̕ϊ��Ɏ��s
    }

    // ���� Direct2D �I�u�W�F�N�g�Ƌ��Ɏg�p�ł��� ID2D1Bitmap �I�u�W�F�N�g���쐬
    hr = mRenderTarget->CreateBitmapFromWicBitmap(converter, &d2dBitmap);
    if (FAILED(hr)) {
        d2dBitmap = nullptr;
    }

cleanup:
    SafeRelease(&converter);
    return d2dBitmap;
}
