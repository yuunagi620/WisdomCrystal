// WICCore.h

#pragma once

#include <wincodec.h>
#include <d2d1.h>
#include <memory>
#include <boost/noncopyable.hpp>

#include "win/COM/Deleter.h"
#include "win/COM/COMPtr.h"


class WICCore : private boost::noncopyable {

public:
    WICCore();
    virtual ~WICCore();

    bool Init(std::shared_ptr<ID2D1RenderTarget> renderTarget);

    // ファイルパスから ID2D1Bitmap を作成する
    ID2D1Bitmap* CreateD2DBitmapFromFile(LPCTSTR imageFilePath);

    // リソースから ID2D1Bitmap を作成する
    ID2D1Bitmap* CreateD2DBitmapFromResource(LPCTSTR resourceName, LPCTSTR resourceType);

private:
    COMPtr<IWICBitmapDecoder>     createDecoder(LPCTSTR imageFilePath);
    COMPtr<IWICBitmapDecoder>     createDecoder(COMPtr<IWICStream> stream);

    COMPtr<IWICBitmapFrameDecode> getFrame(COMPtr<IWICBitmapDecoder> decoder);
    ID2D1Bitmap*                  convertD2DBitmap(COMPtr<IWICBitmapFrameDecode> frame);

private:
    COMPtr<IWICImagingFactory> mWICFactory;
    std::shared_ptr<ID2D1RenderTarget> mRenderTarget;
};
