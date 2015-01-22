// CollisionObject.h

#pragma once

#include "../GameObject.h"
#include "CollisionData.h"
#include "CollisionRectData.h"

class CollisionObject : public GameObject {

public:
    virtual ~CollisionObject() {};
    virtual CollisionData CollisionDetection(const CollisionRectData& rectData) = 0;

};
