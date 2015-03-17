// XA2Core.cpp

#include "XA2Core.h"


XA2Core::XA2Core() : mXAudio(nullptr), mMasteringVoice(nullptr) {
    // empty
}


XA2Core::~XA2Core() {
    // empty
}


bool XA2Core::Init() {

     // XAudio2 オブジェクトの作成
    UINT32 xaudioCreateFlag = 0;
    HRESULT hr = XAudio2Create(&mXAudio, xaudioCreateFlag);
    if (FAILED(hr)) {
        return false;
    }

     // マスターボイスの作成
    hr = mXAudio->CreateMasteringVoice(&mMasteringVoice);
    if (FAILED(hr)) {
        return false;
    }

    return true;
}


std::shared_ptr<IXAudio2SourceVoice> XA2Core::CreateSourceVoice(const WAVEFORMATEX& waveFormatEx,
                                                                IXAudio2VoiceCallback* callback) {
    IXAudio2SourceVoice* tempSourceVoice = nullptr;
    HRESULT hr = mXAudio->CreateSourceVoice(&tempSourceVoice,
                                            &waveFormatEx,
                                            0,
                                            XAUDIO2_DEFAULT_FREQ_RATIO,
                                            callback);
    if (FAILED(hr)) {
        return nullptr;
    }

    // ソースボイス用のデリータ
    auto deleter = [](IXAudio2SourceVoice* ptr) {
        if (ptr != nullptr) {
            ptr->Stop();
            ptr->DestroyVoice();
            ptr = nullptr;
        }
    };

    std::shared_ptr<IXAudio2SourceVoice> sourceVoice(tempSourceVoice, deleter);
    return sourceVoice;
}
