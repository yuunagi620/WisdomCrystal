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


ID2D1Bitmap* WICCore::CreateD2DBitmapFromFile(LPCTSTR imageFilePath) {

    // IWICBitmapDecoder ���쐬
    std::shared_ptr<IWICBitmapDecoder> decoder(createDecoder(imageFilePath),  Deleter<IWICBitmapDecoder>());
    if (decoder == nullptr) {
        return nullptr;
    }

    // �C���[�W���� Frame ���擾
    std::shared_ptr<IWICBitmapFrameDecode> frame(getFrame(decoder), Deleter<IWICBitmapFrameDecode>());
    if (frame == nullptr) {
        return nullptr;
    }

    // Direct2D �Ŏg�p�ł���`���ɕϊ����ĕԂ�
    return convertD2DBitmap(frame);
}


ID2D1Bitmap* WICCore::CreateD2DBitmapFromResource(LPCTSTR resourceName, LPCTSTR resourceType) {

    HMODULE hModule = GetModuleHandle(nullptr);

    // ���\�[�X��T��
    HRSRC imageResHandle = FindResource(hModule, resourceName, resourceType);
    if (imageResHandle == nullptr) {
        return nullptr;
    }

    // ���\�[�X�̃��[�h
    HGLOBAL imageResDataHandle = LoadResource(hModule, imageResHandle);
    if (imageResDataHandle == nullptr) {
        return nullptr;
    }

    // ���\�[�X�����b�N
    void *imageFile = LockResource(imageResDataHandle);
    if (imageFile == nullptr) {
        return nullptr;
    }

    // ���\�[�X�̃T�C�Y���v�Z
    DWORD imageFileSize = SizeofResource(hModule, imageResHandle);
    if (imageFileSize == 0) {
        return nullptr;
    }

    // �X�g���[���̍쐬
    std::shared_ptr<IWICStream> stream(createStream(),  Deleter<IWICStream>());
    if (stream == nullptr) {
        return nullptr;
    }

    // �X�g���[���̃�������������
    HRESULT hr = stream->InitializeFromMemory(reinterpret_cast<BYTE*>(imageFile), imageFileSize);
    if (FAILED(hr)) {
        return nullptr;
    }

    // �f�R�[�_�[�̍쐬
    std::shared_ptr<IWICBitmapDecoder> decoder(createDecoder(stream),  Deleter<IWICBitmapDecoder>());
    if (decoder == nullptr) {
        return nullptr;
    }

    // �C���[�W���� Frame ���擾
    std::shared_ptr<IWICBitmapFrameDecode> frame(getFrame(decoder), Deleter<IWICBitmapFrameDecode>());
    if (frame == nullptr) {
        return nullptr;
    }

    // Direct2D �Ŏg�p�ł���`���ɕϊ����ĕԂ�
    return convertD2DBitmap(frame);
}


IWICBitmapDecoder* WICCore::createDecoder(LPCTSTR imageFilePath) {
    IWICBitmapDecoder *decoder = nullptr;
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


IWICBitmapDecoder* WICCore::createDecoder(std::shared_ptr<IWICStream> stream) {
    IWICBitmapDecoder *decoder = nullptr;
    HRESULT hr = mWICImagingFactory->CreateDecoderFromStream(stream.get(),
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
    HRESULT hr = mWICImagingFactory->CreateStream(&stream);
    if (FAILED(hr)) {
        return nullptr;
    }

    return stream;
}


IWICBitmapFrameDecode* WICCore::getFrame(std::shared_ptr<IWICBitmapDecoder> decoder) {
    IWICBitmapFrameDecode *frame = nullptr;
    HRESULT hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr)) {
        return nullptr;
    }

    return frame;
}


ID2D1Bitmap* WICCore::convertD2DBitmap(std::shared_ptr<IWICBitmapFrameDecode> frame) {

    // converter �̍쐬
    std::shared_ptr<IWICFormatConverter> converter(createConverter(), Deleter<IWICFormatConverter>());
    if (converter == nullptr) {
        return nullptr;
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
