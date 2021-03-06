// D3DCore.cpp

#pragma comment(lib, "d3d10_1.lib")

#include "D3DCore.h"


D3DCore::D3DCore() : mD3DDevice(nullptr), mSwapChain(nullptr), mRenderTargetView(nullptr) {
    // empty
}


D3DCore::~D3DCore() {
    // empty
}


bool D3DCore::Init(const HWND& hWnd, int clientWidth, int clientHeight) {

    // DeviceとSwapChainの作成
    if (createDeviceAndSwapChain(hWnd, clientWidth, clientHeight) == false) {
        return false;
    }

    // RenderTargetView の作成
    if (createRenderTargetView() == false) {
        return false;
    }

    // viewport の登録
    setViewport(clientWidth, clientHeight);

    return true;
}


void D3DCore::SetFullscreenState(bool isFullscreen) const {
    mSwapChain->SetFullscreenState(isFullscreen, nullptr);
}


void D3DCore::Present() const {
    mSwapChain->Present(1, 0);
}


bool D3DCore::createDeviceAndSwapChain(const HWND& hWnd, int clientWidth, int clientHeight) {

    // SwapChain の設定
    DXGI_SWAP_CHAIN_DESC sd;
    SecureZeroMemory(&sd, sizeof(sd));

    sd.BufferDesc.Width = clientWidth;
    sd.BufferDesc.Height = clientHeight;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1; // 60fps
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 1;
    sd.OutputWindow = hWnd;
    sd.Windowed = true;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    // SwapChain とデバイスの作成
    HRESULT hr = D3D10CreateDeviceAndSwapChain1(nullptr,
                                                D3D10_DRIVER_TYPE_HARDWARE,
                                                nullptr,
                                                D3D10_CREATE_DEVICE_BGRA_SUPPORT,
                                                D3D10_FEATURE_LEVEL_10_1,
                                                D3D10_1_SDK_VERSION ,
                                                &sd,
                                                &mSwapChain,
                                                &mD3DDevice);
    if (FAILED(hr)) {
        return false;
    }

    return true;
}


bool D3DCore::createRenderTargetView() {

    //  BackBuffer の確保
    COMPtr<ID3D10Texture2D> backBuffer(nullptr);
    HRESULT hr = mSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<LPVOID*>(&backBuffer));
    if (FAILED(hr)) {
        return false;
    }

    // RenderTargetView の作成
    COMPtr<ID3D10RenderTargetView> renderTargetView(nullptr);
    hr = mD3DDevice->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
    if (FAILED(hr)) {
        return false;
    }

    // RenderTargetView の登録
    mD3DDevice->OMSetRenderTargets(1, &renderTargetView, nullptr);

    return true;
}


void D3DCore::setViewport(const int clientWidth, const int clientHeight) {

    // viewport の設定
    D3D10_VIEWPORT vp;

	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width    = static_cast<UINT>(clientWidth);
	vp.Height   = static_cast<UINT>(clientHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

    // viewport の登録
	mD3DDevice->RSSetViewports(1, &vp);
}
