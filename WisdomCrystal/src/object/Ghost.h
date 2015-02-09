// Ghost.h

#pragma once

#include "GameObject.h"
#include "win/D2D/D2DImage.h"


class Ghost : public GameObject {

public:
    Ghost();
    virtual ~Ghost();

    bool Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) override;
    void Update() override;

private:
    GraphicsDevice* mGraphicsDevice;
    SoundDevice* mSoundDevice;

    D2DImage mImage;
    int mX, mY;
    bool mIsAlive;
};
