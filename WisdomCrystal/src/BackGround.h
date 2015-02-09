// BackGround.h

#pragma once

#include <string>
#include <boost/noncopyable.hpp>

#include "GraphicsDevice.h"
#include "win/D2D/D2DImage.h"


class BackGround : private boost::noncopyable {

public:
    BackGround();
    virtual ~BackGround();

    bool Init(GraphicsDevice *graphicsDevice, const int index = 0);

    void Draw();

    bool ChangeBackGroundImage(const int index);

private:
    void changeImagePath();
    bool setBackGroundImage();
    D2D1_RECT_F getRectF();

private:
    GraphicsDevice* mGraphicsDevice;
    int mImageID;

    std::basic_string<TCHAR> mImagePath;
    D2DImage mImage;
};