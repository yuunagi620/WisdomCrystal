// SoundDevice.cpp

// Includes
#include "SoundDevice.h"


SoundDevice::SoundDevice() {
    // empty
}


SoundDevice::~SoundDevice() {
    Cleanup();
}


bool SoundDevice::Init() {

    // XAudio2 ÇÃèâä˙âª
    if (mXA2Core.Init() == false) {
        MessageBox(nullptr, TEXT("Can not initialize XAudio2."), TEXT("ERROR"), MB_OK);
        return false;
    }

    return true;
}


void SoundDevice::Cleanup() {
    // empty
}


bool SoundDevice::CreateSourceVoice(IXAudio2SourceVoice **sourceVoice,
                                    WAVEFORMATEX *waveFormatEx) {

    return mXA2Core.CreateSourceVoice(sourceVoice, waveFormatEx);
}
