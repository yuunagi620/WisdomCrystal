// Vector2D.h

#pragma once

#include <cmath>


namespace Util {

class Vector2D {

public:
    float x, y;

public:
    Vector2D();
    Vector2D(float initX, float initY);

    virtual ~Vector2D();

    //  2 つの Vector が等しいかどうかを判定します
    inline bool Equals(const Vector2D& v) {
        return ((x == v.x) && (y == v.y));
    }
    
    // このベクトルの長さを取得します
    inline float Length() {
        return std::sqrtf(x * x + y * y);
    }

    // このベクトルの長さの四角形を取得します
    inline float LengthSquared() {
        return (x * x + y * y);
    }

    // このベクトルを正規化します
    inline void Normalize() {
        *this /= std::sqrtf(x * x + y * y);
    }

    // このベクトルを回転させます
    inline void Rotate(const float angle) {
        const float sin = std::sinf(angle);
        const float cos = std::cosf(angle);
    
        const float nx = cos * x - sin * y;
        const float ny = sin * x + cos * y;
    
        x = nx; y = ny;
    }

    // ベクトルの内積を計算
    static inline float Dot(const Vector2D& v1, const Vector2D& v2) {
        return (v1.x * v2.x + v1.y * v2.y);
    }

    // 演算子の定義
    Vector2D& operator = (const Vector2D& v)  { x = v.x;  y = v.y;  return *this; }
    Vector2D& operator +=(const Vector2D& v)  { x += v.x; y += v.y; return *this; }
    Vector2D& operator -=(const Vector2D& v)  { x -= v.x; y -= v.y; return *this; }
    Vector2D& operator *=(const float scalar) { x *= scalar; y *= scalar; return *this; }
    Vector2D& operator /=(const float scalar) { x /= scalar; y /= scalar; return *this; }
    
    Vector2D operator +() const { return *this; }
    Vector2D operator -() const { return Vector2D(-x, -y); }

    Vector2D operator +(const Vector2D &v)  const { return Vector2D(x + v.x   , y + v.y); }
    Vector2D operator -(const Vector2D &v)  const { return Vector2D(x - v.x   , y - v.y); }
    Vector2D operator *(const float scalar) const { return Vector2D(x * scalar, y * scalar); }
    Vector2D operator /(const float scalar) const { return Vector2D(x / scalar, y / scalar); }

    friend Vector2D operator *(float scalar, const Vector2D& v) { return Vector2D(v.x * scalar, v.y * scalar); }
    friend Vector2D operator /(float scalar, const Vector2D& v) { return Vector2D(v.x / scalar, v.y / scalar); }

    bool operator==(const Vector2D& v) const { return  (x == v.x && y == v.y); }
    bool operator!=(const Vector2D& v) const { return !(x == v.x && y == v.y); }
};

} // namespace Util
