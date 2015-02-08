// D3DCore.cpp

// Includes
#include "D3DCore.h"
#include "SwapChainDeleter.h"


D3DCore::D3DCore() : mD3DDevice(nullptr),
                     mSwapChain(nullptr),
                     mRenderTargetView(nullptr)
{
    // empty
}


D3DCore::~D3DCore() {
    // empty
}


bool D3DCore::Init(const HWND& hWnd, const int screenWidth, const int screenHeight) {

    // DeviceとSwapChainの作成
    if (createDeviceAndSwapChain(hWnd, screenWidth, screenHeight) == false) {
        return false;
    }

    // RenderTargetView の作成
    if (createRenderTargetView() == false) {
        return false;
    }

    // viewport の登録
    setViewport(screenWidth, screenHeight);

    return true;
}


void D3DCore::SetFullscreenState(const bool isFullscreen) const {
    mSwapChain->SetFullscreenState(isFullscreen, nullptr);
}


bool D3DCore::createDeviceAndSwapChain(const HWND& hWnd, const int screenWidth, const int screenHeight) {

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

    ID3D10Device1 *device = nullptr;
    IDXGISwapChain *swapChain = nullptr;
    HRESULT hr = D3D10CreateDeviceAndSwapChain1(nullptr,
                                                D3D10_DRIVER_TYPE_HARDWARE,
                                                nullptr,
                                                D3D10_CREATE_DEVICE_BGRA_SUPPORT,
                                                D3D10_FEATURE_LEVEL_10_1,
                                                D3D10_1_SDK_VERSION ,
                                                &sd,
                                                &swapChain,
                                                &device);


    if (FAILED(hr)) {
        return false;
    }

    mD3DDevice.reset(device);
    mSwapChain.reset(swapChain, SwapChainDeleter());
    return true;
}


bool D3DCore::createRenderTargetView() {
    std::unique_ptr<ID3D10Texture2D, Deleter<ID3D10Texture2D>> backBuffer(createBackBuffer());

    //  BackBuffer の確保
    if (backBuffer == nullptr) {
        return false;
    }

    // RenderTargetView の作成
    ID3D10RenderTargetView *renderTargetView = nullptr;
    HRESULT hr = mD3DDevice->CreateRenderTargetView(backBuffer.get(), nullptr, &renderTargetView);
    if (FAILED(hr)) {
        return false;
    }

    // RenderTargetView の登録
	// これでレンダリング結果がSwapChainのバッファに書き込まれる
    mD3DDevice->OMSetRenderTargets(1, &renderTargetView, nullptr);

    mRenderTargetView.reset(renderTargetView);

    return true;
}


ID3D10Texture2D* D3DCore::createBackBuffer() {
    ID3D10Texture2D* buffer;
    HRESULT hr = mSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<LPVOID*>(&buffer));
    if (FAILED(hr)) {
        return nullptr;
    }

    return buffer;
}


void D3DCore::setViewport(const int screenWidth, const int screenHeight) {

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
}
