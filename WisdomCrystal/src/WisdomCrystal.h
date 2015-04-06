// WisdomCrystal.h

#pragma once

#include <fbxsdk.h>
#include <boost/noncopyable.hpp>

#include "WinApplication.h"
#include "win/COM/COMInitializer.h"
#include "win/GraphicsDevice.h"
#include "win/SoundDevice.h"
#include "ogg/OggBGM.h"
#include "object/GameObjManager.h"
#include "scene/SceneChanger.h"
#include "win/wave/BGMData.h"


class WisdomCrystal final : public WinApplication, private boost::noncopyable {

public:
    WisdomCrystal(const HINSTANCE& hInstance,
                  int clientWidth,
                  int clientHeight,
                  LPCTSTR captionName,
                  LPCTSTR windowClassName);

    ~WisdomCrystal();
    int Run() override;

private:
    bool Init() override;
    int MessageLoop() override;
    LRESULT WinMsgHandler(const UINT msg, const WPARAM wParam, const LPARAM lParam) override;
    void onUpdate();
    void onKeyDown(const WPARAM& wParam);
    void getMesh(FbxNode* node);

private:
    bool mIsFullscreen;

    COMInitializer mCOMInitializer;
    GraphicsDevice mGraphicsDevice;
    SoundDevice    mSoundDevice;
    Ogg::OggBGM    mOggBGM;
    GameObjManager mGameObjManager;
    SceneChanger   mSceneChanger;
};
