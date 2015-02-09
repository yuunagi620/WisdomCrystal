// TitleMenu.cpp

// Includes
#include "TitleMenu.h"


TitleMenu::TitleMenu() : mId(0),
                         mX(0),
                         mY(0),
                         mName(),
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
                     const std::basic_string<TCHAR>& name) {
    mId = id;
    mX = x;
    mY = y;
    mName = name;

    if (mText.Init(graphicsDevice) == false) {
        return false;
    }
    mText.SetFontSize(25.0f);

    return true;
}



void TitleMenu::Draw(int id) {

    // ëIëidÇ™äYìñÇµÇΩÇÁêFÇê‘Ç…
    const D2D1_COLOR_F color(mId == id ? D2D1::ColorF(0xff0000) : D2D1::ColorF(0x000000));
    mText.SetColor(color);
    mText.Draw(mName, D2D1::RectF(mX, mY, mX + 100, mY + 100));
}
