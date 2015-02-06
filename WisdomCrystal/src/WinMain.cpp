// WinMain.cpp

#include "WisdomCrystal.h"
#include <crtdbg.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 704;

const LPCTSTR CAPTION_NAME = TEXT("Wisdom Crystal");
const LPCTSTR WINDOW_CLASS_NAME = TEXT("WisdomCrystal");


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
    int returnCode = 0;

    {
        WisdomCrystal wisdomCrystal(hInstance, SCREEN_WIDTH, SCREEN_HEIGHT, CAPTION_NAME, WINDOW_CLASS_NAME);
        returnCode = wisdomCrystal.Run();
    }
    _CrtDumpMemoryLeaks();

    return returnCode;
}


//int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdLine, int cmdShow) {
//    Window window(hInst, 300, 300, TEXT("test01"));
//    return window.Run();
//}