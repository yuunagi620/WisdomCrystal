// Collision.h

#pragma once

typedef enum CollisionFlagTag {
    COLLISION_NONE   = 0x0000,
    COLLISION_TOP    = 0x0001,
    COLLISION_BOTTOM = 0x0002,
    COLLISION_RIGHT  = 0x0004,
    COLLISION_LEFT   = 0x0008,
} CollisionFlag;

// '|' ���Z�q��int�^�łȂ�,CollisionFlag�^�Ԃ��悤�ɂ���.
inline CollisionFlag operator |(CollisionFlag lhs, CollisionFlag rhs) {
    return static_cast<CollisionFlag>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

// '&' ���Z�q��int�^�łȂ�,CollisionFlag�^�Ԃ��悤�ɂ���.
inline CollisionFlag operator &(CollisionFlag lhs, CollisionFlag rhs) {
    return static_cast<CollisionFlag>(static_cast<int>(lhs) & static_cast<int>(rhs));
}


class CollisionData {

public:
    CollisionData(CollisionFlagTag defaultFlag = COLLISION_NONE);

    inline bool Check(CollisionFlag checkFlag) const {
        return ((mFlags & checkFlag) != 0);
    }

    inline void Set(CollisionFlag setFlag) {
        mFlags |= setFlag;
    }

    inline void Reset(CollisionFlag resetFlag) {
        mFlags &= (~resetFlag);
    }

    int mDX;
    int mDY;
private:
    int mFlags;

};