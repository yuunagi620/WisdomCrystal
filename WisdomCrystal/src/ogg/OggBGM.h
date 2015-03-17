// OggBGM.h

#pragma once

#include "OggFile.h"
#include "win/SoundDevice.h"


namespace Ogg {

class OggBGM : public IXAudio2VoiceCallback {

public:
    OggBGM();
    virtual ~OggBGM();

    bool Init(SoundDevice* soundDevice, const std::string& filePath);
    void Start();
    void Stop();
    bool Update();
    void SetVolume(float volume);

    // IXAudio2VoiceCallback のコールバック関数の実装
    void WINAPI OnBufferEnd(void*) { Update(); } // ボイスがバッファーの処理を終了時にUpdateを呼ぶ

    // 何もしないメソッドがあっても全てをオーバーライドする必要がある
    // 以下の関数は何もしないため空にしておく
    void WINAPI OnStreamEnd() {}
    void WINAPI OnVoiceProcessingPassEnd() {}
    void WINAPI OnVoiceProcessingPassStart(UINT32) {}
    void WINAPI OnBufferStart(void*) {}
    void WINAPI OnLoopEnd(void*) {}
    void WINAPI OnVoiceError(void*, HRESULT) {}

private:
    OggFile mOggFile;
    std::shared_ptr<IXAudio2SourceVoice> mSourceVoice;
    int mBufferIndex;
};

} // namespace Ogg
