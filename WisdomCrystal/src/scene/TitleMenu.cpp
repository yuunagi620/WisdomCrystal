// TitleMenu.cpp

// Includes
#include "TitleMenu.h"


TitleMenu::TitleMenu() : mId(0),
                         mX(0),
                         mY(0),
                         mText()
{
    // empty
}


TitleMenu::~TitleMenu() {
    // empty
}


bool TitleMenu::Init(GraphicsDevice* graphicsDevice,
                     SoundDevice*    soundDevice,
                     const int id, const float x, const float y,
                     const std::basic_string<TCHAR>& captionName) {
    mId = id;
    mX = x;
    mY = y;

    if (mText.Init(graphicsDevice) == false) {
        return false;
    }
    mText.SetFontSize(25.0f);

    return true;
}



void TitleMenu::Draw(int id) {

    // 選択idが該当したら色を赤に
    const D2D1_COLOR_F color(mId == id ? D2D1::ColorF(0xff0000) : D2D1::ColorF(0x000000));
    mText.SetColor(color);
    mText.DrawText(TEXT("メニュー"), D2D1::RectF(mX, mY, mX + 100, mY + 100));
}
