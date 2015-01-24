// WisdomCrystal.cpp

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d10_1.lib")
#pragma comment(lib, "Windowscodecs.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "comctl32.lib")

#if(_WIN32_WINNT >= 0x0602) // Windows8 以上の場合
    #pragma comment(lib, "xaudio2.lib")
#endif


// Includes
#include <CommCtrl.h>

#include "WisdomCrystal.h"

#include "win/util/FPSCounter.h"
#include "win/util/HighResolutionTimer.h"
#include "win/joypad/Joypad.h"


WisdomCrystal::WisdomCrystal(const HINSTANCE hInstance,
                             const int screenWidth,
                             const int screenHeight,
                             const LPCTSTR captionName,
                             const LPCTSTR windowClassName)

    : WinApplication(hInstance, screenWidth, screenHeight, captionName, windowClassName),
      mIsFullscreen(false),
      mBGMData(),
      mGraphicsDevice(),
      mSoundDevice(),
      mBackGround(),
      mGameObjManager(),
      mSceneChanger()
{
    // empty
}


WisdomCrystal::~WisdomCrystal() {
    Cleanup();
}


int WisdomCrystal::Run() {
    int returnCode = 0;

    if (Init()) {
        returnCode = MessageLoop();
    }

    Cleanup();
    _CrtDumpMemoryLeaks();

    return returnCode;
}


bool WisdomCrystal::Init() {

    // Windows の初期化
    if (WinApplication::Init() == false) {
        MessageBox(nullptr, TEXT("Can not initialize Window."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // COM の初期化
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
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
    if (mBGMData.Init(&mSoundDevice, TEXT("resources/sound/BGM/bgm_01.wav")) == false) { 
        MessageBox(nullptr, TEXT("Can not initialize BGM Data."), TEXT("ERROR"), MB_OK);
    }

    mBGMData.SetBGMVolume(START_BGM_VOLUME);
    mBGMData.StartBGM();

    // GameObjManager の初期化
    if (mGameObjManager.Init(&mGraphicsDevice, &mSoundDevice) == false) {
        MessageBox(nullptr, TEXT("Can not init GameObjManager."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // 初期の背景の初期化
    if (mBackGround.Init(&mGraphicsDevice, 0) == false) {
        MessageBox(nullptr, TEXT("Can not init BackGround."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // ウィンドウのフルスクリーン化
    mIsFullscreen = false;
    mGraphicsDevice.SetFullScreenState(mIsFullscreen);

    return true;
}


void  WisdomCrystal::Cleanup() {
    mGameObjManager.Cleanup();
    mBGMData.Cleanup();
    mSoundDevice.Cleanup();
    mGraphicsDevice.Cleanup();
    CoUninitialize();
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
            
            UpdateWindow(GetHWnd());
            mBGMData.UpdateBGM();
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
    
    mBackGround.Draw();
    mSceneChanger.UpdateScene(&mGameObjManager);
    

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
        MessageBox(nullptr, TEXT("debug"), TEXT("ERROR"), MB_OK);       
    }

}
