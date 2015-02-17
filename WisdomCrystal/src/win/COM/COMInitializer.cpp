// COMInitializer.cpp

#pragma comment(lib, "Windowscodecs.lib")

#include "COMInitializer.h"


COMInitializer::COMInitializer() {
    // empty
}


COMInitializer::~COMInitializer() {
    CoUninitialize();
}


bool COMInitializer::Init() {
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        return false;
    }

    return true;
}
