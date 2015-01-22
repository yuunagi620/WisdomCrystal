// CollisionObjManager.h

#pragma once

#include "CollisionObject.h"
#include <boost/noncopyable.hpp>

class CollisionObjManager : private boost::noncopyable {

public:
    static CollisionObjManager *GetInstance();
    static std::vector<CollisionObject*> *GetActiveCollisionObjects();

    GameObject *Activate(int initX, int initY, int objID);

private:
    static const int MAX_COLLISON_OBJECTS;

    static CollisionObjManager mCollisionObjManager;
    static std::vector<CollisionObject*> mActiveCollisionObjects;

    CollisionObjManager();
};
