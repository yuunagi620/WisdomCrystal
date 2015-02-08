// WisdomCrystal.h

#pragma once

#include <boost/noncopyable.hpp>

#include "WinApplication.h"
#include "win/COM/COMInitializer.h"
#include "GraphicsDevice.h"
#include "SoundDevice.h"
#include "BackGround.h"
#include "object/GameObjManager.h"
#include "scene/SceneChanger.h"


// スクリーン関係
const double FPS = 60.0;
const int MAP_ROW = 22;
const int MAP_COL = 40;
const int MAX_MAP_CHIP = MAP_ROW * MAP_COL;

// 画像関係
const int MAP_CHIP_WIDTH  = 32;
const int MAP_CHIP_HEIGHT = 32;
const int MAP_CHIP_IMAGE_COL = 10;


// その他
const float START_BGM_VOLUME = 0.4f;


class WisdomCrystal : public WinApplication, private boost::noncopyable {

public:
    WisdomCrystal(const HINSTANCE hInstance,
                  const int screenWidth,
                  const int screenHeight,
                  const LPCTSTR captionName,
                  const LPCTSTR windowClassName);

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
    BGMData        mBGMData;
    BackGround     mBackGround;
    GameObjManager mGameObjManager;
    SceneChanger   mSceneChanger;
};
