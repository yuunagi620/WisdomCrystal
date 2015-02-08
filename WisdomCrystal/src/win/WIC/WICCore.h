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

    // 
    // ファイルパスから ID2D1Bitmap を作成する
    //
    ID2D1Bitmap *CreateD2DBitmap(LPCTSTR imageFilePath);

private:
    IWICBitmapDecoder*     createBitmapDecoder(LPCTSTR imageFilePath);
    IWICBitmapFrameDecode* getFrame(IWICBitmapDecoder *decoder);
    ID2D1Bitmap*           convertD2DBitmap(IWICBitmapFrameDecode *frame);
    IWICFormatConverter*   createConverter();

    std::unique_ptr<IWICImagingFactory, Deleter<IWICImagingFactory>> mWICImagingFactory;
    ID2D1RenderTarget *mRenderTarget;
};
