// RectangleF.h

#pragma once


namespace Util {

class RectangleF {

public:
    float x, y, width, height;

public:
    RectangleF();
    RectangleF(float initX, float initY, float initWidth, float initHeight);

    virtual ~RectangleF();

    //  2 つの四角形が等しいかどうかを判定します
    inline bool Equals(const RectangleF& r) {
        return ((x == r.x) && (y == r.y) && (width == r.width) && (height == r.height));
    }
    
    //  x，y ，width，heightが 0 の場合は true，違えば false を返します
    inline bool IsEmpty() {
        return (x == 0 && y == 0 && width == 0 && height == 0);
    }

    inline float Top()    { return y;          }
    inline float Bottom() { return y + height; }
    inline float Left()   { return x;          }
    inline float Right()  { return x + width;  }

    // 四角形を移動させます
    inline void Offset(float offsetX, float offsetY) {
        x += offsetX;
        y += offsetY;
        width  += offsetX;
        height += offsetY;
    }
};

} // namespace Util
