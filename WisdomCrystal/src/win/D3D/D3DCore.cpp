// D3DCore.cpp

// Includes
#include "D3DCore.h"
#include "win/util/SafeRelease.h"


D3DCore::D3DCore() : mD3DDevice(nullptr),
                     mSwapChain(nullptr),
                     mRenderTargetView(nullptr),
                     mAdapter(nullptr),
                     mOutput(nullptr)
{
    // empty
}


D3DCore::~D3DCore() {
    Cleanup();
}


bool D3DCore::Init(const HWND& hWnd, const int screenWidth, const int screenHeight) {

    HRESULT hr;

    // SwapChain の設定
    DXGI_SWAP_CHAIN_DESC sd;
    SecureZeroMemory(&sd, sizeof(sd));

    sd.BufferDesc.Width = screenWidth;
    sd.BufferDesc.Height = screenHeight;
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

    // DeviceとSwapChainの作成
    hr = D3D10CreateDeviceAndSwapChain1(nullptr,
                                        D3D10_DRIVER_TYPE_HARDWARE,
                                        nullptr,
                                        D3D10_CREATE_DEVICE_BGRA_SUPPORT,
                                        D3D10_FEATURE_LEVEL_10_1,
                                        D3D10_1_SDK_VERSION ,
                                        &sd,
                                        &mSwapChain,
                                        &mD3DDevice);


    if (FAILED(hr)) {
        return false; // DeviceとSwapChainの作成に失敗
    }

    // RenderTargetView の作成
    ID3D10Texture2D* backBuffer;
    hr = mSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<LPVOID*>(&backBuffer));
    if (FAILED(hr)) {
        return false;
    }

    hr = mD3DDevice->CreateRenderTargetView(backBuffer, nullptr, &mRenderTargetView);
    if (FAILED(hr)) {
        return false;
    }

    SafeRelease(&backBuffer);

    // RenderTargetView の登録
	// これでレンダリング結果がSwapChainのバッファに書き込まれる
    mD3DDevice->OMSetRenderTargets(1, &mRenderTargetView, nullptr);

    // viewport の設定
    D3D10_VIEWPORT vp;

	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width    = static_cast<UINT>(screenWidth);
	vp.Height   = static_cast<UINT>(screenHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

    // viewport の登録
	mD3DDevice->RSSetViewports(1, &vp);

    return true;
}


void D3DCore::Cleanup() {
    SafeRelease(&mRenderTargetView);

    if (mSwapChain != nullptr) {

        // SwapChainを解放する前に必ずウィンドウモードに切り替えておく
        SetFullscreenState(false);
        SafeRelease(&mSwapChain);
    }

    SafeRelease(&mD3DDevice);
}


void D3DCore::SetFullscreenState(const bool isFullscreen) const {
    mSwapChain->SetFullscreenState(isFullscreen, mOutput);
}
