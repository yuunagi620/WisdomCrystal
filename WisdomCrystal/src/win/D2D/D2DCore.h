// D2DCore.h

#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <Dwrite.h>

#include <memory>
#include <boost/noncopyable.hpp>


class D2DCore : private boost::noncopyable {

public:
    D2DCore();
    virtual ~D2DCore();

    bool Init(const HWND hWnd, std::shared_ptr<IDXGISwapChain> swapChain);

    void BeginDraw();
    HRESULT EndDraw();

    void ClearScreen(const D2D1_COLOR_F& fillColor);

    void DrawBitmap(ID2D1Bitmap *bitmap,
                    const D2D1_RECT_F& destinationRectangle,
                    const float opacity,
                    const D2D1_RECT_F& sourceRectangle);

    void ResetTransform();
    void FlipHorizontal(const float centerX, const float centerY);
    void FlipVertical(const float centerX, const float centerY);
    void RotateTransform(const float centerX, const float centerY, const float angle);

    inline std::shared_ptr<ID2D1RenderTarget> GetRenderTarget() const {
        return mRenderTarget;
    }
    inline std::shared_ptr<IDWriteFactory> GetWriteFactory() const {
        return mWriteFactory;
    }

private:
    bool createFactory();
    bool createWriteFactory();
    std::shared_ptr<IDXGISurface> createBackBuffer(std::shared_ptr<IDXGISwapChain> swapChain);

    bool createRenderTarget(std::shared_ptr<IDXGISurface> backBuffer,
                            const D2D1_RENDER_TARGET_PROPERTIES& props);

private:
    std::unique_ptr<ID2D1Factory, Deleter<ID2D1Factory>> mD2DFactory;
    std::shared_ptr<IDWriteFactory>    mWriteFactory;
    std::shared_ptr<ID2D1RenderTarget> mRenderTarget;
};
