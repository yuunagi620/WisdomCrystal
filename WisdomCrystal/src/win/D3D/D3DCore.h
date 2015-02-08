// D3DCore.h

#pragma once

#include <Windows.h>
#include <d3d10_1.h>
#include <memory>
#include <boost/noncopyable.hpp>

#include "win/util/Deleter.h"


class D3DCore : private boost::noncopyable {

public:
    D3DCore();
    virtual ~D3DCore();

    bool Init(const HWND& hWnd, const int screenWidth, const int screenHeight);

    void SetFullscreenState(const bool isFullscreen) const;
    
    inline IDXGISwapChain *GetSwapChain() {
        return mSwapChain.get();
    }

private:
    bool createDeviceAndSwapChain(const HWND& hWnd, const int screenWidth, const int screenHeight);
    bool createRenderTargetView();
    ID3D10Texture2D* createBackBuffer();

private:
    std::unique_ptr<ID3D10Device1, Deleter<ID3D10Device1>> mD3DDevice;
    std::shared_ptr<IDXGISwapChain> mSwapChain;
    std::unique_ptr<ID3D10RenderTargetView, Deleter<ID3D10RenderTargetView>> mRenderTargetView;
    IDXGIAdapter           *mAdapter;
    IDXGIOutput            *mOutput;
};
