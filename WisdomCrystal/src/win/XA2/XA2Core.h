// XA2Core.h

#pragma once

#include <XAudio2.h>
#include <memory>
#include <boost/noncopyable.hpp>

#include "win/COM/Deleter.h"
#include "win/COM/COMPtr.h"


class XA2Core : private boost::noncopyable {

public:
    XA2Core();
    virtual ~XA2Core();

    bool Init();

    std::shared_ptr<IXAudio2SourceVoice> CreateSourceVoice(const WAVEFORMATEX& waveFormatEx);

private:
    COMPtr<IXAudio2> mXAudio;
    COMPtr<IXAudio2MasteringVoice> mMasteringVoice;
};
