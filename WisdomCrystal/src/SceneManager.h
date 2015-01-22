// SceneManager.h

#include "scene/Scene.h"
#include <boost/noncopyable.hpp>

class SceneManager : private boost::noncopyable {

public:
    static SceneManager *GetInstance();

    virtual ~SceneManager();

    void UpdateScene();

private:
    static SceneManager mSceneManager;

    std::unique_ptr<Scene> mCurrentScene;

    SceneManager();

};
