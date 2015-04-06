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

    // Window �̏�����
    if (WinApplication::Init() == false) {
        MessageBox(nullptr, TEXT("Window�̏������Ɏ��s���܂���"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // CPU �� DirectXMath �ɑΉ����Ă��邩���ׂ�
    if (DirectX::XMVerifyCPUSupport() == false) {
        MessageBox(nullptr, TEXT("DirectXMath�ɑΉ����Ă��Ȃ�CPU�ł�"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // COM �̏�����
    if (mCOMInitializer.Init() == false) {
        MessageBox(nullptr, TEXT("COM�̏������Ɏ��s���܂���"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // GraphicsDevice �̏�����
    if (mGraphicsDevice.Init(GetHWnd(), GetClientWidth(), GetClientHeight()) == false) {
        MessageBox(nullptr, TEXT("GraphicsDevice�̏������Ɏ��s���܂���"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SoundDevice �̏�����
    if (mSoundDevice.Init() == false) {
        MessageBox(nullptr, TEXT("SoundDevice�̏������Ɏ��s���܂���"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // GameObjManager �̏�����
    if (mGameObjManager.Init(&mGraphicsDevice, &mSoundDevice) == false) {
        MessageBox(nullptr, TEXT("GameObjManager�̏������Ɏ��s���܂���"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SceneChanger �̏�����
    if (mSceneChanger.Init(&mGraphicsDevice, &mSoundDevice, &mGameObjManager) == false) {
        MessageBox(nullptr, TEXT("SceneChanger�̏������Ɏ��s���܂���"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // �E�B���h�E�̃t���X�N���[����
    mIsFullscreen = false;
    mGraphicsDevice.SetFullScreenState(mIsFullscreen);

    // BGMData �̏�����
    if (mOggBGM.Init(&mSoundDevice, "resources/sound/BGM/bgm_04.ogg") == false) { 
        MessageBox(nullptr, TEXT("BGM�̏������Ɏ��s���܂���"), TEXT("ERROR"), MB_OK);
    }

    mOggBGM.SetVolume(1.0f);
    mOggBGM.Start();

    // FBX���Ǘ�����N���X �R�������Ȃ��Ǝn�܂�Ȃ�
    FbxManager* manager = FbxManager::Create();

    // FBX�t�@�C���̃C���|�[�^���쐬�i�������͖��O �K���Ȃ��̂ł����j
    FbxImporter* importer = FbxImporter::Create(manager, "Importer");

    // �V�[���N���X���쐬
    FbxScene* scene = FbxScene::Create(manager, "Scene");

    // FBX�t�@�C����ǂݍ���
    const char* filename = "test02.fbx";
    importer->Initialize(filename);

    // �ǂݍ���FBX�t�@�C������V�[���f�[�^�����o��
    importer->Import(scene);

    // ���b�V���T��
    getMesh(scene->GetRootNode());

    // FBX�J������
    manager->Destroy();

    return true;
}


int WisdomCrystal::MessageLoop() {
    int returnCode = 0;
    bool isError = false;

    FPSCounter fpsCounter;
    HighResolutionTimer timer(1.0 / 60); // 60fps�^�C�}�[���Z�b�g
    
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

            // �ȉ��A���b�Z�[�W���擾���Ȃ������ꍇ�̏���
            if (timer.Elapsed()) { // �^�C�}�[�ɂ��1�b�Ԃ�60��Ă΂��
                onUpdate();
                fpsCounter.CountFPS();
                DebugManager::OutputValue(fpsCounter.GetFPS());
            }
            UpdateWindow(GetHWnd());
        }

    }

    if (isError) {
        MessageBox(nullptr, TEXT("MessageLoop �ŃG���[���������܂���"), TEXT("ERROR"), MB_OK);
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
            // do nothing. Windows �ɂ��w�i�`��̗}��
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
    
    mGraphicsDevice.ClearScreen(D2D1::ColorF(0x000000)); // ���Ŕw�i��h��Ԃ�

    mSceneChanger.UpdateScene();
    
    HRESULT hr = mGraphicsDevice.EndDraw();
    if (hr == D2DERR_RECREATE_TARGET) {
        InvalidateRect(GetHWnd(), nullptr, false);
    }
    
    mGraphicsDevice.Present(); // �����_�����O���ꂽ�C���[�W��\��
    EndPaint(GetHWnd(), &ps);
}


void WisdomCrystal::onKeyDown(const WPARAM& wParam) {

    // ESC �L�[�ŏI��
    if (wParam == VK_ESCAPE) {
        PostQuitMessage(0);
    }

    // F11 �L�[�őS��ʂ̐ؑ�
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
    // ���b�V��
    FbxMesh* mesh = node->GetMesh();

    if(NULL != mesh)
        printf("\nMesh=%s Node=%s", mesh->GetName(), node->GetName());

    // �q�m�[�h
    for(int i = 0; i < node->GetChildCount(); i++) {
        getMesh(node->GetChild(i));
    }
}