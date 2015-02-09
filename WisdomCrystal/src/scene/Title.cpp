// Title.cpp

// Includes
#include "Title.h"
#include "Loading.h"
#include "win/util/Input.h"


Title::Title() : mId(0),
                 mPlay(),
                 mSetting(),
                 mText(),
                 mGraphicsDevice(nullptr),
                 mSoundDevice(nullptr),
                 mDrawSignal(),
                 mNextScene(nullptr)
{
    // empty
}


Title::~Title() {
    // empty
}


bool Title::Init(GraphicsDevice* graphicsDevice,
                 SoundDevice*    soundDevice) {
    mGraphicsDevice = graphicsDevice;
    mSoundDevice = soundDevice;

    // test
    if (mText.Init(mGraphicsDevice) == false) {
        return false;
    }
    mText.SetFontSize(50.0f);

    // �`��V�O�i���Ƀ^�C�g�����ڂ̕`�惁�\�b�h���Z�b�g
    mDrawSignal.connect([this](int id) {mPlay.draw(id);});
    mDrawSignal.connect([this](int id) {mSetting.draw(id);});

    // �I���V�O�i���Ɏ��̍��ڂ𒲂ׂ郁�\�b�h���Z�b�g
    //mNextSignal.connect([this](int id) {return mPlay.next<Playing>(id);});
    //mNextSignal.connect([this](int id) {return mSetting.next<Setting>(id);});

    // ���̃V�[����this�ɂ���B
    mNextScene = this;
}


Scene *Title::Update(GameObjManager *gameObjManager) {

    // �`��
    mText.DrawText(TEXT("�^�C�g��"), D2D1::RectF(250.f, 250.f, 400.f, 300.f));
    

    // ���ڂ̕`�惁�\�b�h���܂Ƃ߂ČĂ�
    mDrawSignal(mId);
    return mNextScene;
}


void Title::KeyDownEvent() {
    if (IsKeyPressed(Input::DOWN)) {
        mId = ++mId > 1 ? 0 : mId;
    } else if (IsKeyPressed(Input::UP)) {
        mId = --mId < 0 ? 1 : mId;
    } else if (IsKeyPressed(Input::SPACE)) {

        // ���̃V�[���𒲂ׂ�B
        //const Scene *next(mNextSignal(mId));
        //mNextScene = next ? next : this;
    }
}


