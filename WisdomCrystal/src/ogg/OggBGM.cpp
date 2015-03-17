// OggBGM.cpp

#include "OggBGM.h"


namespace Ogg {

OggBGM::OggBGM() : mOggFile(), mSourceVoice(nullptr), mBufferIndex(0) {
    // empty
}


OggBGM::~OggBGM() {
    // empty
}


bool OggBGM::Init(SoundDevice* soundDevice, const std::string& filePath) {

    // BGM データの読み込み
    if (mOggFile.Init(filePath) == false) {
        MessageBox(nullptr, TEXT("OggBGM: OggFileの読み込みに失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SourceVoice の作成
    mSourceVoice = soundDevice->CreateSourceVoice(mOggFile.GetWaveFormatEx(), this);
    if (mSourceVoice == nullptr) {
        MessageBox(nullptr, TEXT("OggBGM: SourceVoiceの作成に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    mOggFile.Load(); // 予め，余分に1つ多く読み込んでおく
    Update();
    return true;
}


void OggBGM::Start() {
    mSourceVoice->Start();
}


void OggBGM::Stop() {
    mSourceVoice->Stop();
}


bool OggBGM::Update() {
    mOggFile.Load();

    std::vector<char>* currentBuffer;

    try {
        currentBuffer = &mOggFile.GetBufferPtr()->at(mBufferIndex);
    } catch (const std::out_of_range&) {
        return false; // 範囲外アクセス
    }

    // ボイスキューに新しいバッファーを追加
    XAUDIO2_BUFFER xa2Buffer = {0};
    xa2Buffer.AudioBytes = currentBuffer->size();
    xa2Buffer.pAudioData = reinterpret_cast<unsigned char*>(&currentBuffer->front());
    xa2Buffer.Flags = 0;
    mSourceVoice->SubmitSourceBuffer(&xa2Buffer);

    // 1つインデックスを進めて最大値を超えていたら最初に戻る
    ++mBufferIndex %= mOggFile.GetBufferPtr()->size();

    return true;
}


void OggBGM::SetVolume(float volume) {
    mSourceVoice->SetVolume(volume);
}

} // namespace Ogg
