// Title.h

#pragma once

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>

#include "Scene.h"
#include "TitleMenu.h"

#include "win/util/Input.h"
#include "GraphicsDevice.h"
#include "SoundDevice.h"


class Title : public Scene, private boost::noncopyable {

public:
    Title();
    virtual ~Title();

    bool Init(GraphicsDevice *graphicsDevice, SoundDevice *soundDevice);

    Scene *Update(GameObjManager *gameObjManager) override;

    virtual void KeyDownEvent();

private:
    int mId;
    TitleMenu mPlay;
    TitleMenu mSetting;
    D2DTextData mText;

    GraphicsDevice* mGraphicsDevice;
    SoundDevice*    mSoundDevice;

    boost::signals2::signal<void (int)> mDrawSignal;
    // boost::signals2::signal<Scene *(int)> mNextSignal;
    Scene *mNextScene;
};
