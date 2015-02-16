// WisdomCrystal.cpp

#pragma comment(lib, "Windowscodecs.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "comctl32.lib")

#if(_WIN32_WINNT >= 0x0602) // Windows8 以上の場合
    #pragma comment(lib, "xaudio2.lib")
#endif

#include <CommCtrl.h>

#include "WisdomCrystal.h"
#include "win/util/FPSCounter.h"
#include "win/util/HighResolutionTimer.h"


WisdomCrystal::WisdomCrystal(const HINSTANCE hInstance,
                             const int screenWidth,
                             const int screenHeight,
                             const LPCTSTR captionName,
                             const LPCTSTR windowClassName)

    : WinApplication(hInstance, screenWidth, screenHeight, captionName, windowClassName),
      mIsFullscreen(false),
      mCOMInitializer(),
      mGraphicsDevice(),
      mSoundDevice(),
      mBGMData(),
      mGameObjManager(),
      mSceneChanger()
{
    // empty
}


WisdomCrystal::~WisdomCrystal() {
    // empty
}


int WisdomCrystal::Run() {
    int returnCode = 0;

    if (Init()) {
        returnCode = MessageLoop();
    }

    return returnCode;
}


bool WisdomCrystal::Init() {

    // Windows の初期化
    if (WinApplication::Init() == false) {
        MessageBox(nullptr, TEXT("Can not initialize Window."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // COM の初期化
    if (mCOMInitializer.Init() == false) {
        MessageBox(nullptr, TEXT("Can not initialize COM."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // GraphicsDevice の初期化
    if (mGraphicsDevice.Init(GetHWnd(), GetScreenWidth(), GetScreenHeight()) == false) {
        MessageBox(nullptr, TEXT("Can not initialize GraphicsDevice."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SoundDevice の初期化
    if (mSoundDevice.Init() == false) {
        MessageBox(nullptr, TEXT("Can not initialize SoundDevice."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // BGMData の初期化
    if (mBGMData.Init(&mSoundDevice, "resources/sound/BGM/bgm_02.wav") == false) { 
        MessageBox(nullptr, TEXT("Can not initialize BGM Data."), TEXT("ERROR"), MB_OK);
    }

    mBGMData.SetBGMVolume(START_BGM_VOLUME);
    mBGMData.Start();

    // GameObjManager の初期化
    if (mGameObjManager.Init(&mGraphicsDevice, &mSoundDevice) == false) {
        MessageBox(nullptr, TEXT("Can not initialize GameObjManager."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SceneChanger の初期化
    if (mSceneChanger.Init(&mGraphicsDevice, &mSoundDevice, &mGameObjManager) == false) {
        MessageBox(nullptr, TEXT("Can not initialize SceneChanger."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // ウィンドウのフルスクリーン化
    mIsFullscreen = false;
    mGraphicsDevice.SetFullScreenState(mIsFullscreen);

    return true;
}


int WisdomCrystal::MessageLoop() {
    int returnCode = 0;
    bool isError = false;

    FPSCounter fpsCounter;
    HighResolutionTimer timer(1.0 / FPS); // 1秒間に60回呼ばれるタイマーをセット
    
    for (;;) {
        MSG msg;
        
        if (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE)) {
            int getMessageResult = GetMessage(&msg, nullptr, 0, 0);

            if (getMessageResult > 0) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else if (getMessageResult == -1) {
                isError = true;
                break;
            } else {
                returnCode = msg.wParam;
                break;
            }
        } else {

            // 以下、メッセージを取得しなかった場合の処理
            if (timer.Elapsed()) { // タイマーにより1秒間に60回呼ばれる
                onUpdate();
                fpsCounter.CountFPS();
                DebugManager::OutputValue(fpsCounter.GetFPS());
                
            }
            mBGMData.UpdateBGM();
            UpdateWindow(GetHWnd());
        }

    }

    if (isError) {
        MessageBox(nullptr, TEXT("Can not get message."), TEXT("ERROR"), MB_OK);
    }

    return returnCode;
}


LRESULT WisdomCrystal::WinMsgHandler(const UINT msg, const WPARAM wParam, const LPARAM lParam) {
     switch (msg) {
        case WM_KEYDOWN: {
            onKeyDown(wParam);
	        return 0;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
        case WM_ERASEBKGND: {
            // do nothing. Windows による背景描画の抑制
            return 0;
        }
        default: {
            return DefSubclassProc(GetHWnd(), msg, wParam, lParam);
        }
    }

    return 0;
}


void WisdomCrystal::onUpdate() {
    PAINTSTRUCT ps;

    BeginPaint(GetHWnd(), &ps);
    mGraphicsDevice.BeginDraw();
    
    const D2D1_COLOR_F fillColor = D2D1::ColorF(0x000000); // black
    mGraphicsDevice.ClearScreen(fillColor);

    mSceneChanger.UpdateScene();
    
    HRESULT hr = mGraphicsDevice.EndDraw();
    if (hr == D2DERR_RECREATE_TARGET) {
        InvalidateRect(GetHWnd(), nullptr, false);
    }
    
    mGraphicsDevice.Present(); // レンダリングされたイメージを表示
    EndPaint(GetHWnd(), &ps);
}


void WisdomCrystal::onKeyDown(const WPARAM& wParam) {

    // ESC キーで終了
    if (wParam == VK_ESCAPE) {
        PostQuitMessage(0);
    }

    // F11 キーで全画面の切替
    if (wParam == VK_F11) {
        mIsFullscreen = (!mIsFullscreen);
        mGraphicsDevice.SetFullScreenState(mIsFullscreen);
    }

    // debug
    if (wParam == VK_F1) {
        static bool isOn = true;
        isOn = !isOn;
        isOn ? mBGMData.Start() : mBGMData.Stop() ;
    }

}
