// OggBGM.h

#pragma once

#include "OggFile.h"


namespace Ogg {

class OggBGM {

public:
    OggBGM();
    virtual ~OggBGM();

    bool Init(SoundDevice* soundDevice, const std::string& filePath);

    void Start();
    void Stop();

    void UpdateBGM();

    void SetVolume(const float volume);

private:
    OggFile mOggFile;
    std::shared_ptr<IXAudio2SourceVoice> mSourceVoice;
};

} // namespace Ogg
