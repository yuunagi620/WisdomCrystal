// WisdomCrystal.h

#pragma once

#include <boost/noncopyable.hpp>

#include "WinApplication.h"
#include "win/COM/COMInitializer.h"
#include "GraphicsDevice.h"
#include "SoundDevice.h"
#include "ogg/OggBGM.h"
#include "object/GameObjManager.h"
#include "scene/SceneChanger.h"


class WisdomCrystal : public WinApplication, private boost::noncopyable {

public:
    WisdomCrystal(const HINSTANCE& hInstance,
                  int clientWidth,
                  int clientHeight,
                  LPCTSTR captionName,
                  LPCTSTR windowClassName);

    virtual ~WisdomCrystal();

    virtual int Run() override;

protected:
    virtual bool Init() override;
    virtual int MessageLoop() override;
    virtual LRESULT WinMsgHandler(const UINT msg, const WPARAM wParam, const LPARAM lParam) override;

private:
    void onUpdate();
    void onKeyDown(const WPARAM& wParam);

private:
    bool mIsFullscreen;

    COMInitializer mCOMInitializer;
    GraphicsDevice mGraphicsDevice;
    SoundDevice    mSoundDevice;
    Ogg::OggBGM    mOggBGM;
    GameObjManager mGameObjManager;
    SceneChanger   mSceneChanger;
};
