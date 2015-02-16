// WICCore.h

#pragma once

#include <wincodec.h>
#include <d2d1.h>
#include <boost/noncopyable.hpp>

#include "win/COM/COMPtr.h"


class WICCore : private boost::noncopyable {

public:
    WICCore();
    virtual ~WICCore();

    bool Init(COMPtr<ID2D1RenderTarget> renderTarget);

    // �t�@�C���p�X���� ID2D1Bitmap ���쐬����
    COMPtr<ID2D1Bitmap> CreateBitmapFromFile(LPCTSTR imageFilePath);

    // ���\�[�X���� ID2D1Bitmap ���쐬����
    COMPtr<ID2D1Bitmap> CreateBitmapFromResource(LPCTSTR resourceName, LPCTSTR resourceType);

private:
    COMPtr<IWICBitmapDecoder>     createDecoder(LPCTSTR imageFilePath);
    COMPtr<IWICBitmapDecoder>     createDecoder(COMPtr<IWICStream> stream);
    COMPtr<IWICBitmapFrameDecode> getFrame(COMPtr<IWICBitmapDecoder> decoder);
    COMPtr<ID2D1Bitmap>           convertBitmap(COMPtr<IWICBitmapFrameDecode> frame);

private:
    COMPtr<IWICImagingFactory> mWICFactory;
    COMPtr<ID2D1RenderTarget>  mRenderTarget;
};
