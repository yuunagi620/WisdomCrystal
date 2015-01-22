// Error.h

#pragma once

#include "Scene.h"

class Error : public Scene {

public:
    virtual ~Error() {}
    virtual Scene *Update();

};
