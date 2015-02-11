// WICCore.h

#pragma once

#include <wincodec.h>
#include <d2d1.h>
#include <memory>
#include <boost/noncopyable.hpp>

#include "win/COM/Deleter.h"


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
    IWICBitmapDecoder* createDecoder(LPCTSTR imageFilePath);
    IWICBitmapDecoder* createDecoder(std::shared_ptr<IWICStream> stream);

    IWICStream* createStream();

    IWICBitmapFrameDecode* getFrame(std::shared_ptr<IWICBitmapDecoder> decoder);
    ID2D1Bitmap*           convertD2DBitmap(std::shared_ptr<IWICBitmapFrameDecode> frame);
    IWICFormatConverter*   createConverter();

private:
    std::unique_ptr<IWICImagingFactory, Deleter<IWICImagingFactory>> mWICFactory;
    std::shared_ptr<ID2D1RenderTarget> mRenderTarget;
};
