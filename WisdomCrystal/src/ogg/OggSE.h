// OggSE.h

#pragma once

#include "OggFile.h"
#include "win/SoundDevice.h"


namespace Ogg {

class OggSE {

public:
    OggSE();
    virtual ~OggSE();

    bool Init(SoundDevice* soundDevice, const std::string& filePath);
    void Start();
    void Stop();
    void SetVolume(float volume);

private:
    void resetSourceVoice();

private:
    OggFile mOggFile;
    std::shared_ptr<IXAudio2SourceVoice> mSourceVoice;
};

} // namespace Ogg
