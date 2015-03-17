// Point.h

#pragma once


class Point {

public:
    int x, y;

public:
    Point();
    Point(int initX, int initY);

    virtual ~Point();

    //  2 �̓_�����������ǂ����𔻒肵�܂�
    inline bool Equals(const Point& p) {
        return ((x == p.x) && (y == p.y));
    }
    
    //  x�Cy �̗����� 0 �̏ꍇ�� true�C�Ⴆ�� false ��Ԃ��܂�
    inline bool IsEmpty() {
        return (x == 0 && y == 0);
    }

    // ���Z�q�̒�`
    Point& operator = (const Point& p) { x = p.x;  y = p.y;  return *this; }
    Point& operator +=(const Point& p) { x += p.x; y += p.y; return *this; }
    Point& operator -=(const Point& p) { x -= p.x; y -= p.y; return *this; }
    Point& operator *=(const Point& p) { x *= p.x; y *= p.y; return *this; }
    Point& operator *=(const int n   ) { x *= n;   y *= n;   return *this; }
    Point& operator /=(const Point& p) { x /= p.x; y /= p.y; return *this; }
    Point& operator /=(const int n   ) { x /= n;   y /= n;   return *this; }
    
    Point operator +() const { return *this; }
    Point operator -() const { return Point(-x, -y); }

    Point operator +(const Point &p) const { return Point(x + p.x, y + p.y); }
    Point operator -(const Point &p) const { return Point(x - p.x, y - p.y); }
    Point operator *(const Point &p) const { return Point(x * p.x, y * p.y); }
    Point operator *(const int n   ) const { return Point(x * n  , y * n  ); }
    Point operator /(const Point &p) const { return Point(x / p.x, y / p.y); }
    Point operator /(const int n   ) const { return Point(x / n  , y / n  ); }

    friend Point operator *(int n, const Point& p) { return Point(p.x * n , p.y * n); }
    friend Point operator /(int n, const Point& p) { return Point(p.x / n , p.y / n); }

    bool operator==(const Point& p) const { return  (x == p.x && y == p.y); }
    bool operator!=(const Point& p) const { return !(x == p.x && y == p.y); }
};
