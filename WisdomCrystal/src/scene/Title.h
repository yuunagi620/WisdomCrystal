// Title.h

#pragma once

#include <boost/noncopyable.hpp>
#include <vector>

#include "Scene.h"
#include "TitleMenu.h"
#include "BackGround.h"
#include "Canvas.h"
#include "win/D2D/D2DBrush.h"
#include "win/util/Input.h"


class Title : public Scene, private boost::noncopyable {

public:
    Title();
    virtual ~Title();

    bool Init(GraphicsDevice *graphicsDevice,
              SoundDevice *soundDevice,
              GameObjManager *gameObjManager) override;

    Scene* Update() override;

private:
    void onKeyDown();

private:
    int mId;
    int mKeyWait;

    TitleMenu mPlay;
    TitleMenu mSetting;
    TitleMenu mEnd;

    Canvas     mCanvas;
    D2DText    mText;
    D2DBrush   mBrush;
    BackGround mBackGround;

    Scene *mNextScene;
};
