// Playing.h

#pragma once

#include <boost/noncopyable.hpp>

#include "Scene.h"


class Playing : public Scene, private boost::noncopyable {

public:
    virtual ~Playing();
    virtual Scene *Update(GameObjManager *gameObjManager) override;
};
