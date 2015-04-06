// WisdomCrystal.cpp

#include <CommCtrl.h>
#include <DirectXMath.h>
#include <fbxsdk.h>

#include "WisdomCrystal.h"
#include "win/util/FPSCounter.h"
#include "win/util/HighResolutionTimer.h"


WisdomCrystal::WisdomCrystal(const HINSTANCE& hInstance,
                             int clientWidth,
                             int clientHeight,
                             LPCTSTR captionName,
                             LPCTSTR windowClassName)

    : WinApplication(hInstance, clientWidth, clientHeight, captionName, windowClassName)
    , mIsFullscreen(false)
    , mCOMInitializer()
    , mGraphicsDevice()
    , mSoundDevice()
    , mOggBGM()
    , mGameObjManager()
    , mSceneChanger() {
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
        MessageBox(nullptr, TEXT("Windowの初期化に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // CPU が DirectXMath に対応しているか調べる
    if (DirectX::XMVerifyCPUSupport() == false) {
        MessageBox(nullptr, TEXT("DirectXMathに対応していないCPUです"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // COM の初期化
    if (mCOMInitializer.Init() == false) {
        MessageBox(nullptr, TEXT("COMの初期化に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // GraphicsDevice の初期化
    if (mGraphicsDevice.Init(GetHWnd(), GetClientWidth(), GetClientHeight()) == false) {
        MessageBox(nullptr, TEXT("GraphicsDeviceの初期化に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SoundDevice の初期化
    if (mSoundDevice.Init() == false) {
        MessageBox(nullptr, TEXT("SoundDeviceの初期化に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // GameObjManager の初期化
    if (mGameObjManager.Init(&mGraphicsDevice, &mSoundDevice) == false) {
        MessageBox(nullptr, TEXT("GameObjManagerの初期化に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SceneChanger の初期化
    if (mSceneChanger.Init(&mGraphicsDevice, &mSoundDevice, &mGameObjManager) == false) {
        MessageBox(nullptr, TEXT("SceneChangerの初期化に失敗しました"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // ウィンドウのフルスクリーン化
    mIsFullscreen = false;
    mGraphicsDevice.SetFullScreenState(mIsFullscreen);

    // BGMData の初期化
    if (mOggBGM.Init(&mSoundDevice, "resources/sound/BGM/bgm_04.ogg") == false) { 
        MessageBox(nullptr, TEXT("BGMの初期化に失敗しました"), TEXT("ERROR"), MB_OK);
    }

    mOggBGM.SetVolume(1.0f);
    mOggBGM.Start();

    // FBXを管理するクラス コレを作らないと始まらない
    FbxManager* manager = FbxManager::Create();

    // FBXファイルのインポータを作成（第二引数は名前 適当なものでいい）
    FbxImporter* importer = FbxImporter::Create(manager, "Importer");

    // シーンクラスを作成
    FbxScene* scene = FbxScene::Create(manager, "Scene");

    // FBXファイルを読み込む
    const char* filename = "test02.fbx";
    importer->Initialize(filename);

    // 読み込んだFBXファイルからシーンデータを取り出す
    importer->Import(scene);

    // メッシュ探索
    getMesh(scene->GetRootNode());

    // FBX開放処理
    manager->Destroy();

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
        MessageBox(nullptr, TEXT("MessageLoop でエラーが発生しました"), TEXT("ERROR"), MB_OK);
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
        // empty
    }
}

void WisdomCrystal::getMesh(FbxNode* node) {
    // メッシュ
    FbxMesh* mesh = node->GetMesh();

    if(NULL != mesh)
        printf("\nMesh=%s Node=%s", mesh->GetName(), node->GetName());

    // 子ノード
    for(int i = 0; i < node->GetChildCount(); i++) {
        getMesh(node->GetChild(i));
    }
}