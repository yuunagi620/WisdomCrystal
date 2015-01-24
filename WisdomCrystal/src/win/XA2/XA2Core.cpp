// XA2Core.cpp

// Includes
#include "XA2Core.h"
#include "win/util/SafeRelease.h"


XA2Core::XA2Core() : mXAudio(nullptr), 
                     mMasteringVoice(nullptr)
{
    // empty
}


XA2Core::~XA2Core() {
    Cleanup();
}


bool XA2Core::Init() {
    UINT32 xaudioCreateFlag = 0;

    HRESULT hr = XAudio2Create(&mXAudio, xaudioCreateFlag);
    if (FAILED(hr)) {
        return false; // XAudio2 オブジェクトの作成に失敗
    }

    hr = mXAudio->CreateMasteringVoice(&mMasteringVoice);
    if (FAILED(hr)) {
        SafeRelease(&mXAudio);
        return false; // マスターボイスの作成に失敗
    }

    return true;
}


void XA2Core::Cleanup() {
    if (mMasteringVoice != nullptr) {
        mMasteringVoice->DestroyVoice();
        mMasteringVoice = nullptr;
    }

    SafeRelease(&mXAudio);
}


bool XA2Core::CreateSourceVoice(IXAudio2SourceVoice **sourceVoice,
                                WAVEFORMATEX *waveFormatEx) {

    HRESULT hr = mXAudio->CreateSourceVoice(sourceVoice, waveFormatEx);
    if (FAILED(hr)) {
        return false;
    }

    return true;
}
