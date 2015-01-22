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


// ファイルパスから ID2D1Bitmap を作成する関数
ID2D1Bitmap *WICCore::CreateD2DBitmap(TCHAR *imageFilePath) {

    ID2D1Bitmap *d2dBitmap = nullptr;

    // IWICBitmapDecoder を作成
    IWICBitmapDecoder *decoder = nullptr;
    HRESULT hr = mWICImagingFactory->CreateDecoderFromFilename(imageFilePath,
                                                               nullptr,
                                                               GENERIC_READ,
                                                               WICDecodeMetadataCacheOnLoad,
                                                               &decoder);
    if (FAILED(hr)) {
        return nullptr; // IWICBitmapDecoder の作成に失敗
    }

    // イメージから Frame を取得し、IWICBitmapFrameDecode オブジェクトに格納
    IWICBitmapFrameDecode *frame = nullptr;
    hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr)) {
        goto cleanup; // Frame の確保に失敗
    }

    // Direct2D で使用できる形式に変換
    d2dBitmap = convertD2DBitmap(frame);

cleanup:
    SafeRelease(&frame);
    SafeRelease(&decoder);

    return d2dBitmap;
}


// Bitmap を Direct2D で使用できる形式に変換する関数
ID2D1Bitmap *WICCore::convertD2DBitmap(IWICBitmapFrameDecode *frame) {

    ID2D1Bitmap *d2dBitmap = nullptr;

    // イメージのピクセル形式を 32bppPBGRA に変換
    IWICFormatConverter *converter = nullptr;
    HRESULT hr = mWICImagingFactory->CreateFormatConverter(&converter);
    if (FAILED(hr)) {
        goto cleanup; // IWICFormatConverter の作成に失敗
    }

    hr = converter->Initialize(frame,
                               GUID_WICPixelFormat32bppPBGRA,
                               WICBitmapDitherTypeNone,
                               nullptr,
                               0.0f,
                               WICBitmapPaletteTypeMedianCut);
    if (FAILED(hr)) {
        goto cleanup; // イメージの変換に失敗
    }

    // 他の Direct2D オブジェクトと共に使用できる ID2D1Bitmap オブジェクトを作成
    hr = mRenderTarget->CreateBitmapFromWicBitmap(converter, &d2dBitmap);
    if (FAILED(hr)) {
        d2dBitmap = nullptr;
    }

cleanup:
    SafeRelease(&converter);
    return d2dBitmap;
}
