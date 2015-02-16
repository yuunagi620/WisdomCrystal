// D3DCore.h

#pragma once

#include <Windows.h>
#include <d3d10_1.h>
#include <memory>
#include <boost/noncopyable.hpp>

#include "win/COM/Deleter.h"
#include "win/COM/COMPtr.h"



class D3DCore : private boost::noncopyable {

public:
    D3DCore();
    virtual ~D3DCore();

    bool Init(const HWND& hWnd, const int screenWidth, const int screenHeight);

    void SetFullscreenState(const bool isFullscreen) const;

    void Present() const;
    
    inline COMPtr<IDXGISwapChain> GetSwapChain() const {
        return mSwapChain;
    }

private:
    bool createDeviceAndSwapChain(const HWND& hWnd, const int screenWidth, const int screenHeight);
    bool createRenderTargetView();
    void setViewport(const int screenWidth, const int screenHeight);

private:
    COMPtr<ID3D10Device1>          mD3DDevice;
    COMPtr<ID3D10RenderTargetView> mRenderTargetView;
    COMPtr<IDXGISwapChain>         mSwapChain;
};
