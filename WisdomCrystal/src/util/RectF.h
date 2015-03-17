// RectF.h

#pragma once


class RectF {

public:
    float x, y, width, height;

public:
    RectF();
    RectF(float initX, float initY, float initWidth, float initHeight);

    virtual ~RectF();

    //  2 �̎l�p�`�����������ǂ����𔻒肵�܂�
    inline bool Equals(const RectF& r) {
        return ((x == r.x) && (y == r.y) && (width == r.width) && (height == r.height));
    }
    
    //  x�Cy �Cwidth�Cheight�� 0 �̏ꍇ�� true�C�Ⴆ�� false ��Ԃ��܂�
    inline bool IsEmpty() {
        return (x == 0 && y == 0 && width == 0 && height == 0);
    }

    // �l�p�`���ړ������܂�
    inline void Offset(float offsetX, float offsetY) {
        x += offsetX;
        y += offsetY;
        width  += offsetX;
        height += offsetY;
    }
};
