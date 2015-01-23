// SceneManager.h

#include <boost/noncopyable.hpp>

#include "scene/Scene.h"
#include "object/GameObjManager.h"


class SceneManager : private boost::noncopyable {

public:
    SceneManager();
    virtual ~SceneManager();

    void UpdateScene(GameObjManager *gameObjManager);

private:
    std::unique_ptr<Scene> mCurrentScene;
};
