// PointF.h

#pragma once

#include "Point.h"


class PointF {

public:
    // public メンバ変数
    float x, y;

public:
    PointF();
    PointF(float initX, float initY);

    virtual ~PointF();

    //  2 つの点が等しいかどうかを判定します
    inline bool Equals(const PointF& p) {
        return ((x == p.x) && (y == p.y));
    }
    
    //  x，y の両方が 0 の場合は true，違えば false を返します
    inline bool IsEmpty() {
        return (x == 0.f && y == 0.f);
    }

    // 演算子の定義
    PointF& operator = (const PointF& p) { x = p.x;  y = p.y;  return *this; }
    PointF& operator +=(const PointF& p) { x += p.x; y += p.y; return *this; }
    PointF& operator -=(const PointF& p) { x -= p.x; y -= p.y; return *this; }
    PointF& operator *=(const PointF& p) { x *= p.x; y *= p.y; return *this; }
    PointF& operator *=(const float n  ) { x *= n;   y *= n;   return *this; }
    PointF& operator /=(const PointF& p) { x /= p.x; y /= p.y; return *this; }
    PointF& operator /=(const float n  ) { x /= n;   y /= n;   return *this; }
    
    PointF operator +() const { return *this; }
    PointF operator -() const { return PointF(-x, -y); }

    PointF operator +(const PointF &p) const { return PointF(x + p.x, y + p.y); }
    PointF operator -(const PointF &p) const { return PointF(x - p.x, y - p.y); }
    PointF operator *(const PointF &p) const { return PointF(x * p.x, y * p.y); }
    PointF operator *(const float n  ) const { return PointF(x * n  , y * n  ); }
    PointF operator /(const PointF &p) const { return PointF(x / p.x, y / p.y); }
    PointF operator /(const float n  ) const { return PointF(x / n  , y / n  ); }

    friend PointF operator *(float n, const PointF& p) { return PointF(p.x * n , p.y * n); }
    friend PointF operator /(float n, const PointF& p) { return PointF(p.x / n , p.y / n); }

    bool operator==(const PointF& p) const { return  (x == p.x && y == p.y); }
    bool operator!=(const PointF& p) const { return !(x == p.x && y == p.y); }
};
