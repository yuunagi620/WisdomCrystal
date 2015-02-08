// SoundDevice.cpp

// Includes
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


bool SoundDevice::CreateSourceVoice(IXAudio2SourceVoice **sourceVoice,
                                    const WAVEFORMATEX& waveFormatEx) {

    return mXA2Core.CreateSourceVoice(sourceVoice, waveFormatEx);
}
