// WisdomCrystal.cpp

#include <CommCtrl.h>
#include <DirectXMath.h>

#include "WisdomCrystal.h"
#include "win/util/FPSCounter.h"
#include "win/util/HighResolutionTimer.h"


WisdomCrystal::WisdomCrystal(const HINSTANCE hInstance,
                             const int screenWidth,
                             const int screenHeight,
                             const LPCTSTR captionName,
                             const LPCTSTR windowClassName)
    :
    WinApplication(hInstance, screenWidth, screenHeight, captionName, windowClassName),
    mIsFullscreen(false),
    mCOMInitializer(),
    mGraphicsDevice(),
    mSoundDevice(),
    mOggBGM(),
    mGameObjManager(),
    mSceneChanger() {
    // empty
}


WisdomCrystal::~WisdomCrystal() {
    // empty
}


int WisdomCrystal::Run() {
    if (Init()) {
        return MessageLoop();
    }

    return 0;
}


bool WisdomCrystal::Init() {

    // Window の初期化
    if (WinApplication::Init() == false) {
        MessageBox(nullptr, TEXT("Window の初期化に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // CPU が DirectXMath に対応しているか調べる
    if (DirectX::XMVerifyCPUSupport() == false) {
        MessageBox(nullptr, TEXT("DirectXMath に対応していないCPUです"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // COM の初期化
    if (mCOMInitializer.Init() == false) {
        MessageBox(nullptr, TEXT("COM の初期化に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // GraphicsDevice の初期化
    if (mGraphicsDevice.Init(GetHWnd(), GetScreenWidth(), GetScreenHeight()) == false) {
        MessageBox(nullptr, TEXT("GraphicsDevice の初期化に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SoundDevice の初期化
    if (mSoundDevice.Init() == false) {
        MessageBox(nullptr, TEXT("SoundDevice の初期化に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // GameObjManager の初期化
    if (mGameObjManager.Init(&mGraphicsDevice, &mSoundDevice) == false) {
        MessageBox(nullptr, TEXT("GameObjManager の初期化に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SceneChanger の初期化
    if (mSceneChanger.Init(&mGraphicsDevice, &mSoundDevice, &mGameObjManager) == false) {
        MessageBox(nullptr, TEXT("SceneChanger の初期化に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // ウィンドウのフルスクリーン化
    mIsFullscreen = false;
    mGraphicsDevice.SetFullScreenState(mIsFullscreen);

    // BGMData の初期化
    if (mOggBGM.Init(&mSoundDevice, "resources/sound/BGM/bgm_03.ogg") == false) { 
        MessageBox(nullptr, TEXT("BGM の初期化に失敗しました"), TEXT("ERROR"), MB_OK);
    }

    mOggBGM.SetVolume(0.5f);
    mOggBGM.Start();

    return true;
}


int WisdomCrystal::MessageLoop() {
    int returnCode = 0;
    bool isError = false;

    FPSCounter fpsCounter;
    HighResolutionTimer timer(1.0 / 60); // 60fpsタイマーをセット
    
    for (;;) {
        MSG msg;
        
        if (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE)) {
            int messageResult = GetMessage(&msg, nullptr, 0, 0);

            if (messageResult > 0) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else if (messageResult == -1) {
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
    
    mGraphicsDevice.ClearScreen(D2D1::ColorF(0x000000)); // 黒で背景を塗りつぶす

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
        isOn ? mOggBGM.Start() : mOggBGM.Stop() ;
    }
}
