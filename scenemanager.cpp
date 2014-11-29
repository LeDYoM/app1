#include "scenemanager.h"
#include "renderer.h"
#include "scene.h"
#include "log.h"
#include <QMouseEvent>

#define DO_IF_ACTIVE_SCENE(action)  if (activeScene) { action } else { DEBUG("No active scene"); }

SceneManager::SceneManager(QObject *parent_)
    :QObject(parent_)
{
}

void SceneManager::Render(Renderer *renderer)
{
    renderer->prepareNewFrame();

    DO_IF_ACTIVE_SCENE(activeScene->Render(renderer);)
}

bool SceneManager::event(QEvent *e)
{
    if (e->type() != QEvent::ChildAdded && e->type() != QEvent::ChildRemoved)
    {
        DO_IF_ACTIVE_SCENE(activeScene->event(e);)
    }

    return QObject::event(e);
}

void SceneManager::resize(int w, int h)
{
    DO_IF_ACTIVE_SCENE(activeScene->resize(w,h);)
}
