// WinApplication.cpp

#pragma comment(lib, "comctl32.lib")

#include <CommCtrl.h>
#include "WinApplication.h"


WinApplication::WinApplication(const HINSTANCE& hInstnce,
                               int clientWidth,
                               int clientHeight,
                               LPCTSTR captionName,
                               LPCTSTR windowClassName)
    : mHInstance(hInstnce)
    , mHWnd(nullptr)
    , CLIENT_WIDTH(clientWidth)
    , CLIENT_HEIGHT(clientHeight)
    , CAPTION_NAME(captionName)
    , WINDOW_CLASS_NAME(windowClassName) {
    // empty
}


WinApplication::~WinApplication() {
    // empty
}


int WinApplication::Run() {
    if (Init()) {
        return MessageLoop();
    }

    return 0;
}


// �E�B���h�E�v���V�[�W���̌Ăяo����
LRESULT CALLBACK WinApplication::SubClassProc(const HWND hWnd,
                                              const UINT msg,
                                              const WPARAM wParam,
                                              const LPARAM lParam,
                                              const UINT_PTR thisPtr,
                                              const DWORD_PTR refData) {
    
    // �E�B���h�E�v���V�[�W���̌Ăяo����� static �֐��łȂ���΂Ȃ�Ȃ�����
    // �������g�̃|�C���^���擾���� winMsgHandler �փ��b�Z�[�W������C����
    WinApplication* const WinApplication(reinterpret_cast<WinApplication*>(thisPtr));
    return WinApplication->WinMsgHandler(msg, wParam, lParam);
}



bool WinApplication::Init() {

    // WindowClass �̓o�^
    if (registerWindowClass() == false) {
        MessageBox(nullptr, TEXT("WindowClass �̓o�^�Ɏ��s���܂���"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // Window �̍쐬
    mHWnd = createWindow();
    if (mHWnd == nullptr) {
        MessageBox(nullptr, TEXT("Window ���쐬�ł��܂���ł���"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // �E�B���h�E�v���V�[�W���̊֘A�t����ݒ�
    if (SetWindowSubclass(mHWnd, SubClassProc, reinterpret_cast<UINT_PTR>(this), 0) == false) {
        MessageBox(nullptr, TEXT("�E�B���h�E�v���V�[�W���̊֘A�t���Ɏ��s���܂���"), TEXT("ERROR"), MB_OK);
        return false;
    }

    return true;
}


int WinApplication::MessageLoop() {
    int returnCode = 0;
    bool isError = false;

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
            UpdateWindow(mHWnd);
        }

    }

    if (isError) {
        MessageBox(nullptr, TEXT("MessageLoop �ŃG���[���������܂���"), TEXT("ERROR"), MB_OK);
    }

    return returnCode;
}


LRESULT WinApplication::WinMsgHandler(const UINT msg, const WPARAM wParam, const LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
        default: {
            return DefSubclassProc(mHWnd, msg, wParam, lParam);
        }
    }

    return 0;
}


bool WinApplication::registerWindowClass() {
    WNDCLASSEX wc;
    SecureZeroMemory(&wc, sizeof(wc));

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = DefWindowProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = mHInstance;
    wc.hIcon         = LoadIcon(mHInstance, TEXT("ICON_1"));
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
    wc.lpszMenuName  = nullptr;
    wc.lpszClassName = WINDOW_CLASS_NAME;
    wc.hIconSm       = nullptr;

    return (RegisterClassEx(&wc) != 0);
}


HWND WinApplication::createWindow() {
    const DWORD winsowStyle = (WS_OVERLAPPEDWINDOW ^ WS_SIZEBOX ^ WS_MAXIMIZEBOX) | WS_VISIBLE;

    // �E�B���h�E�T�C�Y���擾
    RECT clientRect = { 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT };
    if (AdjustWindowRectEx(&clientRect, winsowStyle, false, 0) == false) {
        MessageBox(nullptr, TEXT("�E�B���h�E�T�C�Y�̎擾�Ɏ��s���܂���"), TEXT("ERROR"), MB_OK);
        return nullptr;
    }

    return CreateWindowEx(WS_EX_LEFT,
                          WINDOW_CLASS_NAME,
                          CAPTION_NAME,
                          winsowStyle,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          clientRect.right  - clientRect.left,
                          clientRect.bottom - clientRect.top,
                          nullptr,
                          nullptr,
                          mHInstance,
                          nullptr);
}
