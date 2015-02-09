// TitleMenu.h

#pragma once

#include <string>
#include <boost/noncopyable.hpp>

#include "GraphicsDevice.h"
#include "SoundDevice.h"
#include "win/D2D/D2DTextData.h"


class TitleMenu : private boost::noncopyable {

public:
    TitleMenu();
    virtual ~TitleMenu();

    bool Init(GraphicsDevice* graphicsDevice,
              SoundDevice*    soundDevice,
              const int id, const float x, const float y,
              const std::basic_string<TCHAR>& captionName);

    void draw(const int id);

    template <typename T>
    Scene *next(int id) const {
        // �I��id���Y��������V�����V�[���𐶐����ĕԂ�
        // �V�����V�[���̌^�̓e���v���[�g�����œn��
        return (mId == id ? new T() : nullptr);
    }

private:
    int mId;
    float mX;
    float mY;

    D2DTextData mCaptionName;
};
