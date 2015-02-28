// SoundDevice.cpp

#include "SoundDevice.h"


SoundDevice::SoundDevice() {
    // empty
}


SoundDevice::~SoundDevice() {
    // empty
}


bool SoundDevice::Init() {

    // XAudio2 ÇÃèâä˙âª
    if (mXA2Core.Init() == false) {
        MessageBox(nullptr, TEXT("Can not initialize XAudio2."), TEXT("ERROR"), MB_OK);
        return false;
    }

    return true;
}


std::shared_ptr<IXAudio2SourceVoice> SoundDevice::CreateSourceVoice(const WAVEFORMATEX& waveFormatEx) {
    return mXA2Core.CreateSourceVoice(waveFormatEx);
}
