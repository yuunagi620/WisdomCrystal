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

    // IWICBitmapDecoder ���쐬
    auto decoder = createBitmapDecoder(imageFilePath);
    if (decoder == nullptr) {
        return nullptr;
    }

    // �C���[�W���� Frame ���擾
    auto frame = getFrame(decoder);
    if (frame == nullptr) {
        return nullptr;
    }

    // Direct2D �Ŏg�p�ł���`���ɕϊ����ĕԂ�
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

    // converter �̍쐬
    auto converter = createConverter();
    if (converter == nullptr) {
        return nullptr; // converter �̍쐬�Ɏ��s
    }

    // �C���[�W�̃s�N�Z���`���� 32bppPBGRA �ɕϊ�
    HRESULT hr = converter->Initialize(frame.get(),
                                       GUID_WICPixelFormat32bppPBGRA,
                                       WICBitmapDitherTypeNone,
                                       nullptr,
                                       0.0f,
                                       WICBitmapPaletteTypeMedianCut);
    if (FAILED(hr)) {
        return nullptr; // �ϊ��Ɏ��s
    }

    // ID2D1Bitmap �I�u�W�F�N�g���쐬
    ID2D1Bitmap *d2dBitmap = nullptr;
    hr = mRenderTarget->CreateBitmapFromWicBitmap(converter.get(), &d2dBitmap);
    if (FAILED(hr)) {
        d2dBitmap = nullptr; // D2D1Bitmap �I�u�W�F�N�g�̍쐬�Ɏ��s
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
