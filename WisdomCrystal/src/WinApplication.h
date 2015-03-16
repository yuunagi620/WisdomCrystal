// WinApplication.h

#pragma once

#include <Windows.h>


class WinApplication {

public:
    WinApplication(const HINSTANCE& hInstance,
                   int clientWidth = 800,
                   int clientHeight = 600,
                   LPCTSTR captionName = TEXT("WinApplication"),
                   LPCTSTR windowClassName = TEXT("WinApplication"));

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

    inline const HINSTANCE& GetHInstance() const { return mHInstance; }
    inline const HWND& GetHWnd() const { return mHWnd; }
    inline int GetClientWidth()  const { return CLIENT_WIDTH; }
    inline int GetClientHeight() const { return CLIENT_HEIGHT; }

private:
    bool registerWindowClass();
    HWND createWindow();

private:
    const int CLIENT_WIDTH;
    const int CLIENT_HEIGHT;
    const LPCTSTR CAPTION_NAME;
    const LPCTSTR WINDOW_CLASS_NAME;

    HINSTANCE mHInstance;
    HWND mHWnd;
};
