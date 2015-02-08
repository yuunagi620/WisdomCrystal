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
    bool CreateSourceVoice(IXAudio2SourceVoice **sourceVoice,
                           const WAVEFORMATEX& waveFormatEx);
private:
    XA2Core mXA2Core;
};
