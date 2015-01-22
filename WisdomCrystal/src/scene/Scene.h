// Scene.h

#pragma once


class Scene {

public:
    virtual ~Scene() {}
    virtual Scene *Update() = 0;
};
