// GraphicsDevice.h

#pragma once

#include <Windows.h>
#include <boost/noncopyable.hpp>


class GraphicsDevice : private boost::noncopyable {

public:
    GraphicsDevice();
    virtual ~GraphicsDevice();
    
    bool Init(const HWND& hWnd, const int screenWidth, const int screenHeight);

    void BeginDraw();

    HRESULT EndDraw();

    void Present();

    void SetFullScreenState(const bool isFullscreen);

    void ClearScreen(const D2D1_COLOR_F& fillColor);

    ID2D1Bitmap* CreateD2DBitmap(TCHAR* imageFilePath);

    void DrawBitmap(ID2D1Bitmap* bitmap,
                    const D2D1_RECT_F& destinationRectangle,
                    const float opacity,
                    const D2D1_RECT_F& sourceRectangle);

    void ResetTransform();

    void FlipHorizontal(const float centerX, const float centerY);

    void FlipVertical(const float centerX, const float centerY);

    void RotateTransform(const float centerX, const float centerY, const float angle);

    inline ID2D1RenderTarget* GetRenderTarget() const {
        return mRenderTarget.get();
    }
    inline IDWriteFactory* GetWriteFactory() const {
        return mWriteFactory.get();
    }

private:
    D3DCore mD3DCore;
    D2DCore mD2DCore;
    WICCore mWICCore;

    IDXGISwapChain* mSwapChain;
    std::shared_ptr<ID2D1RenderTarget> mRenderTarget;
    std::shared_ptr<IDWriteFactory>    mWriteFactory;
};
