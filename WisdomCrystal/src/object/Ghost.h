// Ghost.h

#pragma once

#include "GameObject.h"
#include "win/Canvas.h"
#include "win/D2D/D2DImage.h"


class Ghost : public GameObject {

public:
    Ghost();
    virtual ~Ghost();

    bool Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) override;
    bool Activate(const int initX, const int initY) override;
    void Update() override;

private:
    Canvas mCanvas;
    SoundDevice* mSoundDevice;

    D2DImage mImage;
    int mX, mY;
    bool mIsAlive;
};
