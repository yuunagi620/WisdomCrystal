// Playing.h

#pragma once

#include <boost/noncopyable.hpp>

#include "Scene.h"


class Playing : public Scene, private boost::noncopyable {

public:
    Playing();
    virtual ~Playing();

    virtual bool Init(GraphicsDevice *graphicsDevice,
                      SoundDevice *soundDevice,
                      GameObjManager *gameObjManager) override;
    virtual Scene* Update() override;

private:
    GameObjManager *mGameObjManager;
};
