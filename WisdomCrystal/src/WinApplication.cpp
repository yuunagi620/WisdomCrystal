// WinApplication.cpp

#pragma comment(lib, "comctl32.lib")

#include "WinApplication.h"
#include <CommCtrl.h>


WinApplication::WinApplication(const HINSTANCE hInstnce,
                               const int screenWidth,
                               const int screenHeight,
                               const LPCTSTR captionName,
                               const LPCTSTR windowClassName)

    : mHInstance(hInstnce),
      mHWnd(nullptr),
      SCREEN_WIDTH(screenWidth),
      SCREEN_HEIGHT(screenHeight),
      CAPTION_NAME(captionName),
      WINDOW_CLASS_NAME(windowClassName)
{
    // empty
}


WinApplication::~WinApplication() {
    // empty
}


int WinApplication::Run() {
    int returnCode = 0;

    if (Init()) {
        returnCode = MessageLoop();
    }

    return returnCode;
}


// ウィンドウプロシージャの呼び出し先
LRESULT CALLBACK WinApplication::SubClassProc(const HWND hWnd,
                                              const UINT msg,
                                              const WPARAM wParam,
                                              const LPARAM lParam,
                                              const UINT_PTR thisPtr,
                                              const DWORD_PTR refData) {
    
    // ウィンドウプロシージャの呼び出し先は static 関数でなければならないため
    // 自分自身のポインタを取得して winMsgHandler へメッセージ処理を任せる
    WinApplication* const WinApplication(reinterpret_cast<WinApplication*>(thisPtr));
    return WinApplication->WinMsgHandler(msg, wParam, lParam);
}



bool WinApplication::Init() {

    // WindowClass の登録
    if (registerWindowClass() == false) {
        MessageBox(nullptr, TEXT("Can not register WindowClass."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // Window の作成
    mHWnd = createWindow();
    if (mHWnd == nullptr) {
        MessageBox(nullptr, TEXT("Can not create window."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // ウィンドウプロシージャの関連付けを設定
    if (SetWindowSubclass(mHWnd, SubClassProc, reinterpret_cast<UINT_PTR>(this), 0) == false) {
        MessageBox(nullptr, TEXT("Can not set \"SubClassProc\"."), TEXT("ERROR"), MB_OK);
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
        MessageBox(nullptr, TEXT("Can not get message."), TEXT("ERROR"), MB_OK);
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
    wc.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
    wc.lpszMenuName  = nullptr;
    wc.lpszClassName = WINDOW_CLASS_NAME;
    wc.hIconSm       = nullptr;

    return (RegisterClassEx(&wc) != 0);
}


HWND WinApplication::createWindow() {     
    return CreateWindowEx(WS_EX_LEFT,
                          WINDOW_CLASS_NAME,
                          CAPTION_NAME,
                          (WS_OVERLAPPEDWINDOW ^ WS_SIZEBOX ^ WS_MAXIMIZEBOX) | WS_VISIBLE,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          SCREEN_WIDTH,
                          SCREEN_HEIGHT,
                          nullptr,
                          nullptr,
                          mHInstance,
                          nullptr);
}
