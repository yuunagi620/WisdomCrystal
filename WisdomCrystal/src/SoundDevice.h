// SoundDevice.h

#pragma once

#include <Windows.h>
#include <boost/noncopyable.hpp>

#include "win/XA2/XA2Core.h"


class SoundDevice : private boost::noncopyable {

public:
    SoundDevice();
    virtual ~SoundDevice();
    bool Init();
    void Cleanup();

    bool CreateSourceVoice(IXAudio2SourceVoice **sourceVoice,
                           WAVEFORMATEX *waveFormatEx);
private:
    XA2Core mXA2Core;
};
