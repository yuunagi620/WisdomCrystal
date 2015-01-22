// CollisionUtil.cpp

// Includes
#include "CollisionUtil.h"


// Static member variables
CollisionUtil CollisionUtil::mCollisionUtil;



CollisionUtil::CollisionUtil() {
    // empty    
}


CollisionUtil *CollisionUtil::GetInstance() {
    return &mCollisionUtil;
}


void CollisionUtil::RectAndRect(const CollisionRectData& rectData,
                                const RECT& targetRect,
                                CollisionData *collisionData) {

    bool isHit = false;
    int numerator = 1; //•ªŽq
    int denominator = 1; //•ª•ê

    int testDx = rectData.dx;
    int testDy = rectData.dy;

    int lastDx = 0;
    int lastDy = 0;

    RECT nextRect = rectData.rect;

    for (int i = 0; i < 4; ++i) {

        nextRect.left   += testDx;
        nextRect.right  += testDx;
        nextRect.top    += testDy;
        nextRect.bottom += testDy;

        numerator *= 2;
        denominator *= 2;

        // ¶‰E”»’è
        if ((rectData.rect.bottom > targetRect.top) && (targetRect.bottom > rectData.rect.top)) {

            if ((targetRect.right > nextRect.left) && (rectData.rect.left > targetRect.left)) {
                collisionData->Set(COLLISION_RIGHT);
                isHit = true;
            }
            if ((nextRect.right > targetRect.left) && (targetRect.right > rectData.rect.right)) {
                collisionData->Set(COLLISION_LEFT);
                isHit = true;
            }

        }

        // ã‰º”»’è
        if ((rectData.rect.right > targetRect.left) && (targetRect.right > rectData.rect.left)) {

            if ((targetRect.bottom > nextRect.top) && (rectData.rect.top > targetRect.top)) {
                collisionData->Set(COLLISION_BOTTOM);
                isHit = true;
            }
            if ((nextRect.bottom > targetRect.top) && (targetRect.bottom > rectData.rect.bottom)) {
                collisionData->Set(COLLISION_TOP);
                isHit = true;
            }

        }

        if (isHit) {
            --numerator;
        } else {
            ++numerator;
            lastDx = testDx;
            lastDy = testDy;
        }

        testDx = rectData.dx * numerator / denominator;
        testDy = rectData.dy * numerator / denominator;

    }

    collisionData->mDX = lastDx;
    collisionData->mDY = lastDy;

}
