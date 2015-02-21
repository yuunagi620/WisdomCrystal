// Color.h

#pragma once


namespace Util {

class Color {

public:
    float r, g, b, a;

public:
    Color();
    Color( float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f );

    virtual ~Color();

    //  2 �̎l�p�`�����������ǂ����𔻒肵�܂�
    inline bool Equals(const Color& r) {
        return ((x == r.x) && (y == r.y) && (width == r.width) && (height == r.height));
    }
    
    //  x�Cy �Cwidth�Cheight�� 0 �̏ꍇ�� true�C�Ⴆ�� false ��Ԃ��܂�
    inline bool IsEmpty() {
        return (x == 0 && y == 0 && width == 0 && height == 0);
    }

    inline int Top()    { return y;          }
    inline int Bottom() { return y + height; }
    inline int Left()   { return x;          }
    inline int Right()  { return x + width;  }

    // �l�p�`���ړ������܂�
    inline void Offset(int offsetX, int offsetY) {
        x += offsetX;
        y += offsetY;
        width  += offsetX;
        height += offsetY;
    }
};

} // namespace Util
