// GameObject.h

#pragma once

#include "GraphicsDevice.h"
#include "SoundDevice.h"


class GameObject {

public:
    virtual ~GameObject() {}

    virtual bool Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) = 0;

    virtual void Cleanup() = 0;

    virtual void Update() = 0;
};
