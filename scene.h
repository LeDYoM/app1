#ifndef SCENE_H
#define SCENE_H

#include "config.h"
#include "sceneobject.h"

class SceneManager;
class Camera;
class Renderer;

class Scene : public QObject
{
    Q_OBJECT
public:
    explicit Scene(SceneManager *scnManager_);
    void resizeGL(int w, int h);
    void Render(Renderer *renderer);

public:
    template <typename T> T* createCamera()
    {
        Camera *temp = new T(this);
        camera = temp;
        return temp;
    }
private:
    Camera *camera;
};

#endif // SCENE_H
