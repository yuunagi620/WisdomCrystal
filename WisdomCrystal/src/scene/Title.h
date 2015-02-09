// Title.h

#pragma once

#include <boost/noncopyable.hpp>

#pragma warning (disable: 4005) // C4005 åxçêñ≥éã
#include <boost/signals2.hpp>
//#pragma warning (default: 4005) // C4005 åxçêâèú

#include "Scene.h"
#include "TitleMenu.h"

#include "win/util/Input.h"
#include "GraphicsDevice.h"
#include "SoundDevice.h"


class Title : public Scene, private boost::noncopyable {

public:
    Title();
    virtual ~Title();

    bool Init(GraphicsDevice *graphicsDevice,
              SoundDevice *soundDevice,
              GameObjManager *gameObjManager) override;

    Scene* Update() override;

    virtual void KeyDownEvent();

private:
    int mId;
    TitleMenu mPlay;
    TitleMenu mSetting;
    D2DTextData mText;

    GraphicsDevice *mGraphicsDevice;
    SoundDevice    *mSoundDevice;

    boost::signals2::signal<void (int)> mDrawSignal;
    Scene *mNextScene;
};
