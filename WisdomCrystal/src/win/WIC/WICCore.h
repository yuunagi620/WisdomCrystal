// WICCore.h

#pragma once

#include <wincodec.h>
#include <boost/noncopyable.hpp>

#include "win/util/Deleter.h"


class WICCore : private boost::noncopyable {

public:
    WICCore();
    ~WICCore();

    bool Init(ID2D1RenderTarget *renderTarget);

    // ファイルパスから ID2D1Bitmap を作成する
    ID2D1Bitmap *CreateD2DBitmap(LPCTSTR imageFilePath);

private:
    std::shared_ptr<IWICBitmapDecoder> createBitmapDecoder(LPCTSTR imageFilePath);
    IWICBitmapFrameDecode* getFrame(std::shared_ptr<IWICBitmapDecoder> decoder);
    ID2D1Bitmap*           convertD2DBitmap(std::shared_ptr<IWICBitmapFrameDecode> frame);
    IWICFormatConverter*   createConverter();

private:
    std::unique_ptr<IWICImagingFactory, Deleter<IWICImagingFactory>> mWICImagingFactory;
    ID2D1RenderTarget *mRenderTarget;
};
