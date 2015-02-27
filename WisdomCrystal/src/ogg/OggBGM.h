// OggBGM.h

#pragma once

#include "OggFile.h"


namespace Ogg {

class OggBGM : private IXAudio2VoiceCallback {

public:
    OggBGM();
    virtual ~OggBGM();

    bool Init(SoundDevice* soundDevice, const std::string& filePath);

    void Start();
    void Stop();

    void UpdateBGM();

    void SetVolume(const float volume);

    void WINAPI OnStreamEnd() {};
    void WINAPI OnVoiceProcessingPassEnd() {};
    void WINAPI OnVoiceProcessingPassStart(UINT32) {};
    void WINAPI OnBufferEnd(void *) {};
    void WINAPI OnBufferStart(void *) {};
    void WINAPI OnLoopEnd(void *) {};
    void WINAPI OnVoiceError(void *, HRESULT) {};

private:
    OggFile mOggFile;
    std::shared_ptr<IXAudio2SourceVoice> mSourceVoice;
    int mBufferIndex;
};

} // namespace Ogg
