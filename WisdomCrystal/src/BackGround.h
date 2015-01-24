// BackGround.h

#pragma once

#include <boost/noncopyable.hpp>

#include "GraphicsDevice.h"
#include "win/util/WinString.h"


class BackGround : private boost::noncopyable {

public:
    BackGround();
    virtual ~BackGround();

    bool Init(GraphicsDevice* graphicsDevice, const int index = 0);

    void Draw();

    bool ChangeBackGroundImage(const int index);

private:
    static const WinString IMAGE_PATH;
    static const WinString FILENAME;
    static const WinString FILENAME_EXTENSION;
 
    void changeImagePath();
    bool setBackGroundImage();
    D2D1_RECT_F getRectF();

    GraphicsDevice* mGraphicsDevice;
    WinString mImagePath;
    int mImageID;

    D2D1_SIZE_U mImageSize;
    D2D1_RECT_F mImageSrcRect;
    ID2D1Bitmap *mImage;
};