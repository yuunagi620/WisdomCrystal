// XA2Core.h

#pragma once

#include <XAudio2.h>
#include <memory>
#include <boost/noncopyable.hpp>

#include "MasteringVoiceDeleter.h"
#include "XAudio2Deleter.h"


class XA2Core : private boost::noncopyable {

public:
    XA2Core();
    virtual ~XA2Core();

    bool Init();

    bool CreateSourceVoice(IXAudio2SourceVoice **sourceVoice,
                           WAVEFORMATEX *waveFormatEx);

private:
    bool createMasteringVoice();
    bool createXAudio2();

    std::unique_ptr<IXAudio2, XAudio2Deleter> mXAudio;
    std::unique_ptr<IXAudio2MasteringVoice, MasteringVoiceDeleter> mMasteringVoice;
};
