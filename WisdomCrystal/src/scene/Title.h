// Title.h

#pragma once

#include <boost/noncopyable.hpp>

#include "Scene.h"


class Title : public Scene, private boost::noncopyable {

public:
    virtual ~Title();
    virtual Scene *Update(GameObjManager *gameObjManager) override;
};
