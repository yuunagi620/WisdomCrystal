// XA2Core.cpp

// Includes
#include "XA2Core.h"


XA2Core::XA2Core() : mXAudio(nullptr), 
                     mMasteringVoice(nullptr)
{
    // empty
}


XA2Core::~XA2Core() {
    // empty
}


bool XA2Core::Init() {
    if (createXAudio2() == false) {
        return false; // XAudio2 オブジェクトの作成に失敗
    }
    if (createMasteringVoice() == false) {
        return false; // マスターボイスの作成に失敗
    }

    return true;
}


bool XA2Core::CreateSourceVoice(IXAudio2SourceVoice **sourceVoice,
                                WAVEFORMATEX *waveFormatEx) {

    HRESULT hr = mXAudio->CreateSourceVoice(sourceVoice, waveFormatEx);
    if (FAILED(hr)) {
        return false;
    }

    return true;
}


bool XA2Core::createMasteringVoice() {
    IXAudio2MasteringVoice *masteringVoice = nullptr;
    if (FAILED(mXAudio->CreateMasteringVoice(&masteringVoice))) {
        return false;
    }
    mMasteringVoice.reset(masteringVoice);
    return true;
}


bool XA2Core::createXAudio2() {
    UINT32 xaudioCreateFlag = 0;
    IXAudio2 *xAudio2 = nullptr;
    if (FAILED(XAudio2Create(&xAudio2, xaudioCreateFlag))) {
        return false;
    }
    mXAudio.reset(xAudio2);
    return true;
}