// Window.h

#pragma once

#include <Windows.h>

class Window {

public:
    Window(const HINSTANCE hInstance,
           const int screenWidth = 800,
           const int screenHeight = 600,
           const LPCTSTR captionName = TEXT("Window"),
           const LPCTSTR windowClassName = TEXT("Window"));

    virtual ~Window();

    virtual int Run();

    static LRESULT CALLBACK SubClassProc(const HWND hWnd,
                                         const UINT msg,
                                         const WPARAM wParam,
                                         const LPARAM lParam,
                                         const UINT_PTR thisPtr,
                                         const DWORD_PTR refData);

protected:
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    const LPCTSTR CAPTION_NAME;
    const LPCTSTR WINDOW_CLASS_NAME;

    virtual bool Init();
    virtual int MessageLoop();
    virtual LRESULT WinMsgHandler(const UINT msg, const WPARAM wParam, const LPARAM lParam);

    inline HINSTANCE GetHInstance() const {
        return mHInstance;
    }
    inline HWND GetHWnd() const {
        return mHWnd;
    }

private:
    bool registerWindowClass();
    HWND createWindow();

    HINSTANCE mHInstance;
    HWND mHWnd;
};
