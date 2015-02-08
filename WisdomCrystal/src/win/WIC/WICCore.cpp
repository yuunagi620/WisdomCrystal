// WICCore.cpp

// Includes
#include "WICCore.h"


WICCore::WICCore() : mWICImagingFactory(nullptr),
                     mRenderTarget(nullptr)                 
{
    // empty
}


WICCore::~WICCore() {
    // empty
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


ID2D1Bitmap *WICCore::CreateD2DBitmap(LPCTSTR imageFilePath) {

    // IWICBitmapDecoder ���쐬
    std::shared_ptr<IWICBitmapDecoder> decoder = nullptr;
    decoder.reset(createBitmapDecoder(imageFilePath), Deleter<IWICBitmapDecoder>());
    if (decoder == nullptr) {
        return nullptr;
    }

    // �C���[�W���� Frame ���擾
    std::shared_ptr<IWICBitmapFrameDecode> frame = nullptr;
    frame.reset(getFrame(decoder), Deleter<IWICBitmapFrameDecode>());
    if (frame == nullptr) {
        return nullptr;
    }

    // Direct2D �Ŏg�p�ł���`���ɕϊ����ĕԂ�
    return convertD2DBitmap(frame);
}


IWICBitmapDecoder* WICCore::createBitmapDecoder(LPCTSTR imageFilePath) {
    IWICBitmapDecoder *decoder;
    HRESULT hr = mWICImagingFactory->CreateDecoderFromFilename(imageFilePath,
                                                               nullptr,
                                                               GENERIC_READ,
                                                               WICDecodeMetadataCacheOnLoad,
                                                               &decoder);
    if (FAILED(hr)) {
        return nullptr;
    }

    return decoder;
}


IWICBitmapFrameDecode* WICCore::getFrame(std::shared_ptr<IWICBitmapDecoder> decoder) {
    IWICBitmapFrameDecode *frame = nullptr;
    HRESULT hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr)) {
        return nullptr;
    }

    return frame;
}


ID2D1Bitmap *WICCore::convertD2DBitmap(std::shared_ptr<IWICBitmapFrameDecode> frame) {

    // converter �̍쐬
    std::unique_ptr<IWICFormatConverter, Deleter<IWICFormatConverter>> converter(createConverter());
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


IWICFormatConverter* WICCore::createConverter() {
    IWICFormatConverter *converter = nullptr;
    HRESULT hr = mWICImagingFactory->CreateFormatConverter(&converter);
    if (FAILED(hr)) {
        return nullptr;
    }

    return converter;
}
