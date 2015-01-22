// CollisionUtil.h

#pragma once

#include "object/CollisionObject/CollisionData.h"
#include "object/CollisionObject/CollisionRectData.h"

#include <boost/noncopyable.hpp>

class CollisionUtil : private boost::noncopyable {

public:
    static CollisionUtil *GetInstance();

    void CollisionUtil::RectAndRect(const CollisionRectData& rectData,
                                    const RECT& targetRect,
                                    CollisionData *collisionData);

private:
    static CollisionUtil mCollisionUtil;

    CollisionUtil();

};
