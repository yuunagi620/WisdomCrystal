// WICCore.cpp

#include "WICCore.h"


WICCore::WICCore() : mWICFactory(nullptr),
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
                                  reinterpret_cast<void **>(&mWICFactory));
    if (FAILED(hr)) {
        return false;
    }

    return true;
}


ID2D1Bitmap* WICCore::CreateD2DBitmapFromFile(LPCTSTR imageFilePath) {

    // IWICBitmapDecoder を作成
    std::shared_ptr<IWICBitmapDecoder> decoder(createDecoder(imageFilePath),  Deleter<IWICBitmapDecoder>());
    if (decoder == nullptr) {
        return nullptr;
    }

    // イメージから Frame を取得
    std::shared_ptr<IWICBitmapFrameDecode> frame(getFrame(decoder), Deleter<IWICBitmapFrameDecode>());
    if (frame == nullptr) {
        return nullptr;
    }

    // Direct2D で使用できる形式に変換して返す
    return convertD2DBitmap(frame);
}


ID2D1Bitmap* WICCore::CreateD2DBitmapFromResource(LPCTSTR resourceName, LPCTSTR resourceType) {

    HMODULE hModule = GetModuleHandle(nullptr);

    // リソースを探す
    HRSRC imageResHandle = FindResource(hModule, resourceName, resourceType);
    if (imageResHandle == nullptr) {
        return nullptr;
    }

    // リソースのロード
    HGLOBAL imageResDataHandle = LoadResource(hModule, imageResHandle);
    if (imageResDataHandle == nullptr) {
        return nullptr;
    }

    // リソースをロック
    void *imageFile = LockResource(imageResDataHandle);
    if (imageFile == nullptr) {
        return nullptr;
    }

    // リソースのサイズを計算
    DWORD imageFileSize = SizeofResource(hModule, imageResHandle);
    if (imageFileSize == 0) {
        return nullptr;
    }

    // ストリームの作成
    COMPtr<IWICStream> stream(nullptr);
    HRESULT hr = mWICFactory->CreateStream(&stream);
    if (FAILED(hr)) {
        return nullptr;
    }

    // ストリームのメモリを初期化
    hr = stream->InitializeFromMemory(reinterpret_cast<BYTE*>(imageFile), imageFileSize);
    if (FAILED(hr)) {
        return nullptr;
    }

    // デコーダーの作成
    std::shared_ptr<IWICBitmapDecoder> decoder(createDecoder(stream),  Deleter<IWICBitmapDecoder>());
    if (decoder == nullptr) {
        return nullptr;
    }

    // イメージから Frame を取得
    std::shared_ptr<IWICBitmapFrameDecode> frame(getFrame(decoder), Deleter<IWICBitmapFrameDecode>());
    if (frame == nullptr) {
        return nullptr;
    }

    // Direct2D で使用できる形式に変換して返す
    return convertD2DBitmap(frame);
}


IWICBitmapDecoder* WICCore::createDecoder(LPCTSTR imageFilePath) {
    IWICBitmapDecoder *decoder = nullptr;
    HRESULT hr = mWICFactory->CreateDecoderFromFilename(imageFilePath,
                                                        nullptr,
                                                        GENERIC_READ,
                                                        WICDecodeMetadataCacheOnLoad,
                                                        &decoder);
    if (FAILED(hr)) {
        return nullptr;
    }
    return decoder;
}


IWICBitmapDecoder* WICCore::createDecoder(COMPtr<IWICStream> stream) {
    IWICBitmapDecoder *decoder = nullptr;
    HRESULT hr = mWICFactory->CreateDecoderFromStream(stream,
                                                      nullptr,
                                                      WICDecodeMetadataCacheOnLoad,
                                                      &decoder);
    if (FAILED(hr)) {
        return nullptr;
    }
    return decoder;
}


IWICStream* WICCore::createStream() {
    IWICStream *stream = nullptr;
    HRESULT hr = mWICFactory->CreateStream(&stream);
    if (FAILED(hr)) {
        return nullptr;
    }

    return stream;
}


COMPtr<IWICBitmapFrameDecode> WICCore::getFrame(std::shared_ptr<IWICBitmapDecoder> decoder) {
    COMPtr<IWICBitmapFrameDecode> frame(nullptr);
    HRESULT hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr)) {
        return nullptr;
    }

    return frame;
}


ID2D1Bitmap* WICCore::convertD2DBitmap(std::shared_ptr<IWICBitmapFrameDecode> frame) {

    // converter の作成
    COMPtr<IWICFormatConverter> converter(nullptr);
    HRESULT hr = mWICFactory->CreateFormatConverter(&converter);
    if (FAILED(hr)) {
        return nullptr;
    }

    // イメージのピクセル形式を 32bppPBGRA に変換
    hr = converter->Initialize(frame.get(),
                               GUID_WICPixelFormat32bppPBGRA,
                               WICBitmapDitherTypeNone,
                               nullptr,
                               0.0f,
                               WICBitmapPaletteTypeMedianCut);
    if (FAILED(hr)) {
        return nullptr;
    }

    // ID2D1Bitmap オブジェクトを作成
    ID2D1Bitmap *d2dBitmap = nullptr;
    hr = mRenderTarget->CreateBitmapFromWicBitmap(converter, &d2dBitmap);
    if (FAILED(hr)) {
        d2dBitmap = nullptr;
    }

    return d2dBitmap;
}

