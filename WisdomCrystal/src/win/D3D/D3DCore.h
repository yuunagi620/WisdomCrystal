// D3DCore.h

#pragma once

#include <Windows.h>
#include <d3d10_1.h>
#include <boost/noncopyable.hpp>


class D3DCore : private boost::noncopyable {

public:
    D3DCore();
    virtual ~D3DCore();

    bool Init(const HWND& hWnd, const int screenWidth, const int screenHeight);

    void Cleanup();

    void SetFullscreenState(const bool isFullscreen) const;
    
    inline IDXGISwapChain *GetSwapChain() const {
        return mSwapChain;
    }

private:
    ID3D10Device1          *mD3DDevice;
    IDXGISwapChain         *mSwapChain;
    ID3D10RenderTargetView *mRenderTargetView;
    IDXGIAdapter           *mAdapter;
    IDXGIOutput            *mOutput;

};
