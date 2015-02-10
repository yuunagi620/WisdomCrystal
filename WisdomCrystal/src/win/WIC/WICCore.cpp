// WICCore.cpp

#include "WICCore.h"


WICCore::WICCore() : mWICImagingFactory(nullptr),
                     mRenderTarget(nullptr)                 
{
    // empty
}


WICCore::~WICCore() {
    // empty
}


bool WICCore::Init(std::shared_ptr<ID2D1RenderTarget> renderTarget) {
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


ID2D1Bitmap *WICCore::CreateD2DBitmap(LPCTSTR imageFilePath) {

    // IWICBitmapDecoder を作成
    auto decoder = createBitmapDecoder(imageFilePath);
    if (decoder == nullptr) {
        return nullptr;
    }

    // イメージから Frame を取得
    auto frame = getFrame(decoder);
    if (frame == nullptr) {
        return nullptr;
    }

    // Direct2D で使用できる形式に変換して返す
    return convertD2DBitmap(frame);
}


std::shared_ptr<IWICBitmapDecoder> WICCore::createBitmapDecoder(LPCTSTR imageFilePath) {
    IWICBitmapDecoder *tempDecoder;
    HRESULT hr = mWICImagingFactory->CreateDecoderFromFilename(imageFilePath,
                                                               nullptr,
                                                               GENERIC_READ,
                                                               WICDecodeMetadataCacheOnLoad,
                                                               &tempDecoder);
    if (FAILED(hr)) {
        return nullptr;
    }

    std::shared_ptr<IWICBitmapDecoder> decoder(tempDecoder,  Deleter<IWICBitmapDecoder>());
    return decoder;
}


std::shared_ptr<IWICBitmapFrameDecode> WICCore::getFrame(std::shared_ptr<IWICBitmapDecoder> decoder) {
    IWICBitmapFrameDecode *tempFrame = nullptr;
    HRESULT hr = decoder->GetFrame(0, &tempFrame);
    if (FAILED(hr)) {
        return nullptr;
    }

    std::shared_ptr<IWICBitmapFrameDecode> frame(tempFrame, Deleter<IWICBitmapFrameDecode>());
    return frame;
}


ID2D1Bitmap* WICCore::convertD2DBitmap(std::shared_ptr<IWICBitmapFrameDecode> frame) {

    // converter の作成
    auto converter = createConverter();
    if (converter == nullptr) {
        return nullptr; // converter の作成に失敗
    }

    // イメージのピクセル形式を 32bppPBGRA に変換
    HRESULT hr = converter->Initialize(frame.get(),
                                       GUID_WICPixelFormat32bppPBGRA,
                                       WICBitmapDitherTypeNone,
                                       nullptr,
                                       0.0f,
                                       WICBitmapPaletteTypeMedianCut);
    if (FAILED(hr)) {
        return nullptr; // 変換に失敗
    }

    // ID2D1Bitmap オブジェクトを作成
    ID2D1Bitmap *d2dBitmap = nullptr;
    hr = mRenderTarget->CreateBitmapFromWicBitmap(converter.get(), &d2dBitmap);
    if (FAILED(hr)) {
        d2dBitmap = nullptr; // D2D1Bitmap オブジェクトの作成に失敗
    }

    return d2dBitmap;
}


std::shared_ptr<IWICFormatConverter> WICCore::createConverter() {
    IWICFormatConverter *tempConverter = nullptr;
    HRESULT hr = mWICImagingFactory->CreateFormatConverter(&tempConverter);
    if (FAILED(hr)) {
        return nullptr;
    }

    std::shared_ptr<IWICFormatConverter> converter(tempConverter, Deleter<IWICFormatConverter>());
    return converter;
}
