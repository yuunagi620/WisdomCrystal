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
    ID2D1Bitmap *CreateD2DBitmap(TCHAR *imageFilePath);

private:
    ID2D1Bitmap *convertD2DBitmap(IWICBitmapFrameDecode *frame);

    std::unique_ptr<IWICImagingFactory, Deleter<IWICImagingFactory>> mWICImagingFactory;
    ID2D1RenderTarget  *mRenderTarget;
};
