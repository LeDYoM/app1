#include "scenemanager.h"
#include "renderer.h"
#include "scene.h"
#include "log.h"

SceneManager::SceneManager(QObject *parent_)
    :QObject(parent_)
{
}

void SceneManager::Render(Renderer *renderer)
{
    renderer->prepareNewFrame();

    DEBUG_IF(!activeScene,"No active scene")

    if (activeScene)
    {
        activeScene->Render(renderer);
    }
}
