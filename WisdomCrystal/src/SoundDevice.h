// SoundDevice.h

#pragma once

#include <Windows.h>
#include <boost/noncopyable.hpp>


class SoundDevice : private boost::noncopyable {

public:
    SoundDevice();
    virtual ~SoundDevice();
    bool Init();

    // ソースボイスの作成
    std::shared_ptr<IXAudio2SourceVoice> CreateSourceVoice(const WAVEFORMATEX& waveFormatEx,
                                                           IXAudio2VoiceCallback* callback = nullptr);

private:
    XA2Core mXA2Core;
};
