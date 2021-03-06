// GameObject.h

#pragma once

#include "win/GraphicsDevice.h"
#include "win/SoundDevice.h"


class GameObject {

public:
    GameObject();
    virtual ~GameObject();

    virtual bool Init(GraphicsDevice *graphicsDevice, SoundDevice *soundDevice) = 0;
    virtual bool Activate(const int initX, const int initY) = 0;
    virtual void Update() = 0;

    virtual inline void SetIsAlive(bool isAlive) { mIsAlive = isAlive; }
    virtual inline bool GetIsAlive() const { return mIsAlive; }

private:
    bool mIsAlive;
};
