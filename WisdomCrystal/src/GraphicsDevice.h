// GraphicsDevice.h

#pragma once

#include <boost/noncopyable.hpp>

#include "win/WIC/WICCore.h"


class GraphicsDevice : private boost::noncopyable {

public:
    GraphicsDevice();
    virtual ~GraphicsDevice();
    
    bool Init(const HWND& hWnd, int clientWidth, int clientHeight);

    void BeginDraw();
    HRESULT EndDraw();
    void Present();
    void SetFullScreenState(bool isFullscreen);
    void ClearScreen(const D2D1_COLOR_F& fillColor);

    COMPtr<ID2D1Bitmap> CreateBitmapFromFile(LPCTSTR imageFilePath);
    COMPtr<ID2D1Bitmap> CreateBitmapFromResource(LPCTSTR resourceName, LPCTSTR resourceType);

    inline COMPtr<ID2D1RenderTarget> GetRenderTarget() const {
        return mD2DCore.GetRenderTarget();
    }

    inline COMPtr<IDWriteFactory> GetWriteFactory() const {
        return mD2DCore.GetWriteFactory();
    }

private:
    D3DCore mD3DCore;
    D2DCore mD2DCore;
    WICCore mWICCore;
};
