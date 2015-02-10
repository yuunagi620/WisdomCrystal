// GraphicsDevice.h

#pragma once

#include <Windows.h>
#include <boost/noncopyable.hpp>

#include "win/WIC/WICCore.h"


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

    ID2D1Bitmap* CreateD2DBitmap(LPCTSTR imageFilePath);

    ID2D1Bitmap* CreateD2DBitmap(LPCTSTR resourceName, LPCTSTR resourceType);

    void DrawBitmap(ID2D1Bitmap* bitmap,
                    const D2D1_RECT_F& destinationRectangle,
                    const float opacity,
                    const D2D1_RECT_F& sourceRectangle);

    void ResetTransform();

    void FlipHorizontal(const float centerX, const float centerY);

    void FlipVertical(const float centerX, const float centerY);

    void RotateTransform(const float centerX, const float centerY, const float angle);

    inline std::shared_ptr<ID2D1RenderTarget> GetRenderTarget() const {
        return mD2DCore.GetRenderTarget();
    }
    inline std::shared_ptr<IDWriteFactory> GetWriteFactory() const {
        return mD2DCore.GetWriteFactory();
    }

private:
    D3DCore mD3DCore;
    D2DCore mD2DCore;
    WICCore mWICCore;
};
