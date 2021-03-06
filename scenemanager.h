#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "config.h"
#include "properties.h"
#include <QObject>
#include "childrencontainer.h"

class Scene;
class Renderer;

class SceneManager : public QObject, public ChildrenContainer<Scene>
{
    Q_OBJECT

    DEF_PROPERTY(Scene*,activeScene,ActiveScene)

public:
    SceneManager(QObject *parent);

public:
    template <typename T> T *createScene()
    {
        T *scn = new T(this);
        _children.push_back(scn);
        return scn;
    }

    void Render(Renderer *renderer);
    bool event(QEvent *);
    void resize(int w, int h);


};

#endif // SCENEMANAGER_H
