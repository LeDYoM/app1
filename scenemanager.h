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

    DEF_Q_PROPERTY_W_DEFAULT(Scene*,activeScene,0)

public:
    SceneManager(QObject *parent);

public:
    template <typename T> T *createScene()
    {
        Scene *scn = new T(this);
        _children.push_back(scn);
        return scn;
    }

    void Render(Renderer *renderer);
};

#endif // SCENEMANAGER_H
