#include "scenemanager.h"
#include "renderer.h"
#include "scene.h"
#include "log.h"

#define DO_IF_ACTIVE_SCENE(action)  if (activeScene) { action } else { DEBUG("No active scene"); }

SceneManager::SceneManager(QObject *parent_)
    :QObject(parent_)
{
}

void SceneManager::Render(Renderer *renderer)
{
    renderer->prepareNewFrame();

    DEBUG_IF(!activeScene,"No active scene")
    DO_IF_ACTIVE_SCENE(activeScene->Render(renderer);)

    if (activeScene)
    {
        activeScene->Render(renderer);
    }
}

void SceneManager::mousePressEvent(QMouseEvent *e)
{
    DO_IF_ACTIVE_SCENE(activeScene->mousePressEvent(e);)
}

void SceneManager::mouseReleaseEvent(QMouseEvent *e)
{
    DO_IF_ACTIVE_SCENE(activeScene->mouseReleaseEvent(e);)
}

void SceneManager::timerEvent(QTimerEvent *e)
{
    DO_IF_ACTIVE_SCENE(activeScene->timerEvent(e);)
}

void SceneManager::resize(int w, int h)
{
    DO_IF_ACTIVE_SCENE(activeScene->resize(w,h);)
}
