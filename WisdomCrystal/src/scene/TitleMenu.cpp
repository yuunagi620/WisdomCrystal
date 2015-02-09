// TitleMenu.cpp

// Includes
#include "TitleMenu.h"
#include "Loading.h"
#include "win/util/Input.h"



TitleMenu::TitleMenu() : mId(0),
                         mX(0),
                         mY(0),
                         mCaptionName()
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

    if (mCaptionName.Init(graphicsDevice) == false) {
        return false;
    }
    mCaptionName.SetFontSize(50.0f);
}



void TitleMenu::draw(const int id) {

    // 選択idが該当したら色を赤に
    const D2D1_COLOR_F color(mId == id ? D2D1::ColorF(0xff0000) : D2D1::ColorF(0x000000));
    mCaptionName.SetColor(color);
    mCaptionName.DrawText(TEXT("タイトル画面"), D2D1::RectF(250.f, 250.f, 400.f, 300.f));
}
