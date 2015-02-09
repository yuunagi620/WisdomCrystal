// SceneChanger.h

#include <boost/noncopyable.hpp>

#include "scene/Scene.h"
#include "object/GameObjManager.h"


class SceneChanger : private boost::noncopyable {

public:
    SceneChanger();
    virtual ~SceneChanger();

    bool Init(GraphicsDevice *graphicsDevice, SoundDevice *soundDevice);

    void UpdateScene(GameObjManager *gameObjManager);

private:
    std::unique_ptr<Scene> mCurrentScene;

    GraphicsDevice* mGraphicsDevice;
    SoundDevice*    mSoundDevice;
};
