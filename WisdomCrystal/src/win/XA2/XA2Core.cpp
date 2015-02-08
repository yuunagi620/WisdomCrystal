// XA2Core.cpp

// Includes
#include "XA2Core.h"
#include "SourceVoiceDeleter.h"


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
        return false; // XAudio2 �I�u�W�F�N�g�̍쐬�Ɏ��s
    }
    if (createMasteringVoice() == false) {
        return false; // �}�X�^�[�{�C�X�̍쐬�Ɏ��s
    }

    return true;
}


std::shared_ptr<IXAudio2SourceVoice> XA2Core::CreateSourceVoice(const WAVEFORMATEX& waveFormatEx) {
    IXAudio2SourceVoice *tempSourceVoice = nullptr;
    HRESULT hr = mXAudio->CreateSourceVoice(&tempSourceVoice, &waveFormatEx);
    if (FAILED(hr)) {
        return nullptr;
    }

    std::shared_ptr<IXAudio2SourceVoice> sourceVoice(tempSourceVoice, SourceVoiceDeleter());
    return sourceVoice;
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