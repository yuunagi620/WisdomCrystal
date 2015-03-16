// BackGround.h

#pragma once

#include <boost/noncopyable.hpp>

#include "GraphicsDevice.h"
#include "win/D2D/D2DImage.h"


class BackGround : private boost::noncopyable {

public:
    BackGround();
    virtual ~BackGround();

    bool Init(GraphicsDevice *graphicsDevice, int imageID = 0);

    void Draw();
    bool ChangeBackGroundImage(int imageID);

private:
    GraphicsDevice* mGraphicsDevice;
    int mImageID;
    D2DImage mImage;
};