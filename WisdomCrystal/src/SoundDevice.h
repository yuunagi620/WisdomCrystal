// SoundDevice.h

#pragma once

#include <Windows.h>
#include <memory>
#include <boost/noncopyable.hpp>

#include "StdAfx.h"


class SoundDevice : private boost::noncopyable {

public:
    SoundDevice();
    virtual ~SoundDevice();
    bool Init();
    void Cleanup();

    bool CreateSourceVoice(IXAudio2SourceVoice **sourceVoice,
                           const WAVEFORMATEX& waveFormatEx);
private:
    XA2Core mXA2Core;
};
