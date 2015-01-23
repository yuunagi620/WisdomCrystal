// Loading.h

#pragma once

#include <boost/noncopyable.hpp>

#include "Scene.h"


class Loading : public Scene, private boost::noncopyable {

public:
    virtual ~Loading();
    virtual Scene *Update(GameObjManager *gameObjManager) override;
};
