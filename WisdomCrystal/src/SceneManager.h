// SceneManager.h

#include <boost/noncopyable.hpp>

#include "scene/Scene.h"


class SceneManager : private boost::noncopyable {

public:
    SceneManager();
    virtual ~SceneManager();

    void UpdateScene();

private:
    std::unique_ptr<Scene> mCurrentScene;
};
