// Loading.h

#pragma once

#include <boost/noncopyable.hpp>

#include "Scene.h"


class Loading : public Scene, private boost::noncopyable {

public:
    Loading();
    virtual ~Loading();

    virtual bool Init(GraphicsDevice *graphicsDevice,
                      SoundDevice *soundDevice,
                      GameObjManager *gameObjManager) override;
    virtual Scene *Update() override;
};
