// Point.h

#pragma once


class Point {

public:
    // public �����o�ϐ�
    int x, y;

public:
    Point();
    Point(int initX, int initY);

    virtual ~Point();

    //  2 �̓_�����������ǂ����𔻒肵�܂�
    inline bool Equals(const Point& other) {
        return (x == other.x && y == other.y);
    }
    
    //  x�Cy �̗����� 0 �̏ꍇ�� true�C�Ⴆ�� false ��Ԃ��܂�
    inline bool IsEmpty() {
        return (x == 0 && y == 0);
    }

    const Point& operator +=(const Point& v) { x += v.x; y += v.y; return *this; }
    const Point& operator -=(const Point& v) { x -= v.x; y -= v.y; return *this; }
    const Point& operator *=(const Point& v) { x *= v.x; y *= v.y; return *this; }
    const Point& operator /=(const Point& v) { x /= v.x; y /= v.y; return *this; }
    const Point& operator *=(const int n   ) { x *= n;   y *= n;   return *this; }
    const Point& operator /=(const int n   ) { x /= n;   y /= n;   return *this; }
    const Point& operator = (const Point& v) { x = v.x;  y = v.y;  return *this; }
    
    friend Point operator +( const Point& v0, const Point& v1 ){
                         Point V( v0.x + v1.x, v0.y + v1.y ); return V; }
    friend Point operator -( const Point& v0, const Point& v1 ){
                         Point V( v0.x - v1.x, v0.y - v1.y ); return V; }

    friend Point operator *( const Point& v0, int n ){
                         Point V( v0.x * n, v0.y * n ); return V; }
    friend Point operator *( int n, const Point& v0 ){
                         Point V( v0.x * n, v0.y * n ); return V; }
    friend Point operator *( const Point& v0, float f ){
                         Point V( (int)( (float)v0.x * f ), (int)( (float)v0.y * f ) ); return V; }
    friend Point operator *( float f, const Point& v0 ){
                         Point V( (int)( (float)v0.x * f ), (int)( (float)v0.y * f ) ); return V; }

    friend Point operator /( const Point& v0, int n ){
                         Point V( v0.x / n, v0.y / n ); return V; }
    friend Point operator /( int n, const Point& v0 ){
                         Point V( v0.x / n, v0.y / n ); return V; }
    friend Point operator /( const Point& v0, float f ){
                         Point V( (int)( (float)v0.x / f ), (int)( (float)v0.y / f ) ); return V; }
    friend Point operator /( float f, const Point& v0 ){
                         Point V( (int)( (float)v0.x / f ), (int)( (float)v0.y / f ) ); return V; }

};
