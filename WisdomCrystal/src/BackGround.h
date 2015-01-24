// BackGround.h

#pragma once

#include <string>
#include <boost/noncopyable.hpp>

#include "GraphicsDevice.h"



class BackGround : private boost::noncopyable {

public:
    BackGround();
    virtual ~BackGround();

    bool Init(GraphicsDevice* graphicsDevice, const int index = 0);

    void Draw();

    bool ChangeBackGroundImage(const int index);

private:
    void changeImagePath();
    bool setBackGroundImage();
    D2D1_RECT_F getRectF();

    static const std::basic_string<TCHAR> IMAGE_PATH;
    static const std::basic_string<TCHAR> FILENAME;
    static const std::basic_string<TCHAR> FILENAME_EXTENSION;

    GraphicsDevice* mGraphicsDevice;
    int mImageID;

    std::basic_string<TCHAR> mImagePath;

    D2D1_SIZE_U mImageSize;
    D2D1_RECT_F mImageSrcRect;
    ID2D1Bitmap *mImage;
};