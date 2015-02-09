// SceneChanger.h

#include <boost/noncopyable.hpp>

#include "scene/Scene.h"
#include "object/GameObjManager.h"


class SceneChanger : private boost::noncopyable {

public:
    SceneChanger();
    virtual ~SceneChanger();

    bool SceneChanger::Init(GraphicsDevice *graphicsDevice,
                            SoundDevice *soundDevice,
                            GameObjManager *gameObjManager);

    bool UpdateScene();

private:
    bool initNextScene();

private:
    std::unique_ptr<Scene> mCurrentScene;

    GraphicsDevice *mGraphicsDevice;
    SoundDevice    *mSoundDevice;
    GameObjManager *mGameObjManager;
};
