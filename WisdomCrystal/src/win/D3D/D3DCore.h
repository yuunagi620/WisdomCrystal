// D3DCore.h

#pragma once

#include <Windows.h>
#include <d3d10_1.h>
#include <boost/noncopyable.hpp>

#include "win/COM/COMPtr.h"


class D3DCore : private boost::noncopyable {

public:
    D3DCore();
    virtual ~D3DCore();

    bool Init(const HWND& hWnd, int clientWidth, int clientHeight);

    void SetFullscreenState(bool isFullscreen) const;
    void Present() const;
    
    inline COMPtr<IDXGISwapChain> GetSwapChain() const { return mSwapChain; }

private:
    bool createDeviceAndSwapChain(const HWND& hWnd, int clientWidth, int clientHeight);
    bool createRenderTargetView();
    void setViewport(const int clientWidth, const int clientHeight);

private:
    COMPtr<ID3D10Device1>          mD3DDevice;
    COMPtr<ID3D10RenderTargetView> mRenderTargetView;
    COMPtr<IDXGISwapChain>         mSwapChain;
};
