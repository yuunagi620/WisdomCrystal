// Error.h

#pragma once

#include <boost/noncopyable.hpp>

#include "Scene.h"


class Error : public Scene, private boost::noncopyable {

public:
    virtual ~Error();
    virtual Scene *Update() override;
};
