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

    // IWICBitmapDecoder ���쐬
    auto decoder = createDecoder(imageFilePath);
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
    COMPtr<IWICStream> stream(nullptr);
    HRESULT hr = mWICFactory->CreateStream(&stream);
    if (FAILED(hr)) {
        return nullptr;
    }

    // �X�g���[���̃�������������
    hr = stream->InitializeFromMemory(reinterpret_cast<BYTE*>(imageFile), imageFileSize);
    if (FAILED(hr)) {
        return nullptr;
    }

    // �f�R�[�_�[�̍쐬
    auto decoder = createDecoder(stream);
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


COMPtr<IWICBitmapDecoder> WICCore::createDecoder(LPCTSTR imageFilePath) {
    COMPtr<IWICBitmapDecoder> decoder(nullptr);
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


COMPtr<IWICBitmapDecoder> WICCore::createDecoder(COMPtr<IWICStream> stream) {
    COMPtr<IWICBitmapDecoder> decoder(nullptr);
    HRESULT hr = mWICFactory->CreateDecoderFromStream(stream,
                                                      nullptr,
                                                      WICDecodeMetadataCacheOnLoad,
                                                      &decoder);
    if (FAILED(hr)) {
        return nullptr;
    }

    return decoder;
}


COMPtr<IWICBitmapFrameDecode> WICCore::getFrame(COMPtr<IWICBitmapDecoder> decoder) {
    COMPtr<IWICBitmapFrameDecode> frame(nullptr);
    HRESULT hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr)) {
        return nullptr;
    }

    return frame;
}


ID2D1Bitmap* WICCore::convertD2DBitmap(COMPtr<IWICBitmapFrameDecode> frame) {

    // converter �̍쐬
    COMPtr<IWICFormatConverter> converter(nullptr);
    HRESULT hr = mWICFactory->CreateFormatConverter(&converter);
    if (FAILED(hr)) {
        return nullptr;
    }

    // �C���[�W�̃s�N�Z���`���� 32bppPBGRA �ɕϊ�
    hr = converter->Initialize(frame,
                               GUID_WICPixelFormat32bppPBGRA,
                               WICBitmapDitherTypeNone,
                               nullptr,
                               0.0f,
                               WICBitmapPaletteTypeMedianCut);
    if (FAILED(hr)) {
        return nullptr;
    }

    // ID2D1Bitmap �I�u�W�F�N�g���쐬
    ID2D1Bitmap *d2dBitmap = nullptr;
    hr = mRenderTarget->CreateBitmapFromWicBitmap(converter, &d2dBitmap);
    if (FAILED(hr)) {
        d2dBitmap = nullptr;
    }

    return d2dBitmap;
}

