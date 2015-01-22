// WICCore.h

#pragma once

#include <wincodec.h>
#include <boost/noncopyable.hpp>


class WICCore : private boost::noncopyable {

public:
    WICCore();
    ~WICCore();

    bool Init(ID2D1RenderTarget *renderTarget);
    void Cleanup();

    // �t�@�C���p�X���� ID2D1Bitmap ���쐬����
    ID2D1Bitmap *CreateD2DBitmap(TCHAR *imageFilePath);

private:
    ID2D1Bitmap *convertD2DBitmap(IWICBitmapFrameDecode *frame);

    IWICImagingFactory *mWICImagingFactory;
    ID2D1RenderTarget  *mRenderTarget;
};
