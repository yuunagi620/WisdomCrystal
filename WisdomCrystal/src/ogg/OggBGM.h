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

    // IXAudio2VoiceCallback �̃R�[���o�b�N�֐��̎���
    void WINAPI OnBufferEnd(void*) { Update(); } // �{�C�X���o�b�t�@�[�̏������I������Update���Ă�

    // �������Ȃ����\�b�h�������Ă��S�Ă��I�[�o�[���C�h����K�v������
    // �ȉ��̊֐��͉������Ȃ����ߋ�ɂ��Ă���
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
