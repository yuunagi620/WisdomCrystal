// TitleMenu.h

#pragma once

#include <string>
#include <boost/noncopyable.hpp>

#include "win/GraphicsDevice.h"
#include "win/SoundDevice.h"
#include "win/D2D/D2DText.h"


class TitleMenu : private boost::noncopyable {

public:
    TitleMenu();
    virtual ~TitleMenu();

    bool Init(GraphicsDevice *graphicsDevice,
              SoundDevice *soundDevice,
              const int id, const float x, const float y,
              const std::basic_string<TCHAR>& name);

    void Draw(int id);

private:
    int mId;
    float mX;
    float mY;

    std::basic_string<TCHAR> mName;
    D2DText mText;
};
