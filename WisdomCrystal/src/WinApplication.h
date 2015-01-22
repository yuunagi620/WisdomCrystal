// WinApplication.h

#pragma once

#include <Windows.h>


class WinApplication {

public:
    WinApplication(const HINSTANCE hInstance,
                   const int screenWidth = 800,
                   const int screenHeight = 600,
                   const LPCTSTR captionName = TEXT("WinApplication"),
                   const LPCTSTR windowClassName = TEXT("WinApplication"));

    virtual ~WinApplication();

    virtual int Run();

    static LRESULT CALLBACK SubClassProc(const HWND hWnd,
                                         const UINT msg,
                                         const WPARAM wParam,
                                         const LPARAM lParam,
                                         const UINT_PTR thisPtr,
                                         const DWORD_PTR refData);

protected:
    virtual bool Init();
    virtual int MessageLoop();
    virtual LRESULT WinMsgHandler(const UINT msg, const WPARAM wParam, const LPARAM lParam);

    inline HINSTANCE GetHInstance() const {
        return mHInstance;
    }
    inline HWND GetHWnd() const {
        return mHWnd;
    }
    inline int GetScreenWidth() const {
        return SCREEN_WIDTH;
    }
    inline int GetScreenHeight() const {
        return SCREEN_HEIGHT;
    }

private:
    bool registerWindowClass();
    HWND createWindow();

    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    const LPCTSTR CAPTION_NAME;
    const LPCTSTR WINDOW_CLASS_NAME;

    HINSTANCE mHInstance;
    HWND mHWnd;
};
