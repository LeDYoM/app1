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

void SceneManager::mousePressEvent(QMouseEvent *e)
{

}

void SceneManager::mouseReleaseEvent(QMouseEvent *e)
{

}

void SceneManager::timerEvent(QTimerEvent *e)
{

}

void SceneManager::resize(int w, int h)
{

}
