// XA2Core.h

#pragma once

#include <XAudio2.h>
#include <boost/noncopyable.hpp>


class XA2Core : private boost::noncopyable {

public:
    XA2Core();
    virtual ~XA2Core();

    bool Init();

    void Cleanup();

    bool CreateSourceVoice(IXAudio2SourceVoice **sourceVoice,
                           WAVEFORMATEX *waveFormatEx);

private:
    IXAudio2 *mXAudio;
    IXAudio2MasteringVoice *mMasteringVoice;
};
