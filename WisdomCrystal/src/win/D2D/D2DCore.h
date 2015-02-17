// D2DCore.h

#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <Dwrite.h>
#include <boost/noncopyable.hpp>

#include "win/COM/COMPtr.h"


class D2DCore : private boost::noncopyable {

public:
    D2DCore();
    virtual ~D2DCore();

    bool Init(const HWND& hWnd, COMPtr<IDXGISwapChain> swapChain);

    void BeginDraw();

    HRESULT EndDraw();

    void ClearScreen(const D2D1_COLOR_F& fillColor);

    inline COMPtr<ID2D1RenderTarget> GetRenderTarget() const {
        return mRenderTarget;
    }
    inline COMPtr<IDWriteFactory> GetWriteFactory() const {
        return mWriteFactory;
    }

private:
    bool createFactory();
    bool createWriteFactory();

private:
    COMPtr<ID2D1Factory>      mD2DFactory;
    COMPtr<IDWriteFactory>    mWriteFactory;
    COMPtr<ID2D1RenderTarget> mRenderTarget;
};
