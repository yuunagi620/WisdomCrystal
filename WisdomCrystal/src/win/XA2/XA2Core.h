// XA2Core.h

#pragma once

#if(_WIN32_WINNT >= 0x0602) // Windows8 à»è„ÇÃèÍçá
    #pragma comment(lib, "xaudio2.lib")
#endif

#include <XAudio2.h>
#include <memory>
#include <boost/noncopyable.hpp>

#include "win/COM/COMPtr.h"


class XA2Core : private boost::noncopyable {

public:
    XA2Core();
    virtual ~XA2Core();

    bool Init();

    std::shared_ptr<IXAudio2SourceVoice> CreateSourceVoice(const WAVEFORMATEX& waveFormatEx,
                                                           IXAudio2VoiceCallback* callback);

private:
    COMPtr<IXAudio2> mXAudio;
    COMPtr<IXAudio2MasteringVoice> mMasteringVoice;
};
