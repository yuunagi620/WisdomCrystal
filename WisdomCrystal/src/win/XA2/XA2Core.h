// XA2Core.h

#pragma once

#include <XAudio2.h>
#include <memory>
#include <boost/noncopyable.hpp>

#include "win/util/Deleter.h"
#include "MasteringVoiceDeleter.h"


class XA2Core : private boost::noncopyable {

public:
    XA2Core();
    virtual ~XA2Core();

    bool Init();

    std::shared_ptr<IXAudio2SourceVoice> CreateSourceVoice(const WAVEFORMATEX& waveFormatEx);

private:
    bool createMasteringVoice();
    bool createXAudio2();

private:
    std::unique_ptr<IXAudio2, Deleter<IXAudio2>> mXAudio;
    std::unique_ptr<IXAudio2MasteringVoice, MasteringVoiceDeleter> mMasteringVoice;
};
