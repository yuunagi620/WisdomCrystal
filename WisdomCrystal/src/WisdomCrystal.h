// WisdomCrystal.h

#pragma once

#include <boost/noncopyable.hpp>

#include "WinApplication.h"
#include "GraphicsDevice.h"
#include "SoundDevice.h"
#include "BackGround.h"


// ÉXÉNÉäÅ[Éìä÷åW
const double FPS = 60.0;
const int MAP_ROW = 22;
const int MAP_COL = 40;
const int MAX_MAP_CHIP = MAP_ROW * MAP_COL;

// âÊëúä÷åW
const int MAP_CHIP_WIDTH  = 32;
const int MAP_CHIP_HEIGHT = 32;
const int MAP_CHIP_IMAGE_COL = 10;
const int GAME_OBJECT_NUM = 2;


// ÇªÇÃëº
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
    virtual void Cleanup();
    virtual int MessageLoop() override;
    virtual LRESULT WinMsgHandler(const UINT msg, const WPARAM wParam, const LPARAM lParam) override;

private:
    void onUpdate();
    void onKeyDown(const WPARAM& wParam);

    bool mIsFullscreen;
    BGMData mBGMData;

    GraphicsDevice mGraphicsDevice;
    SoundDevice mSoundDevice;
    BackGround mBackGround;
};
