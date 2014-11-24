#include "scene.h"
#include "renderer.h"
#include "camera.h"
#include "scenemanager.h"

Scene::Scene(SceneManager *scnManager_)
    :QObject(scnManager_)
{
}

void Scene::Render(Renderer *renderer)
{
    camera->Render(renderer);
}

void Scene::mousePressEvent(QMouseEvent *e)
{

}

void Scene::mouseReleaseEvent(QMouseEvent *e)
{

}

void Scene::timerEvent(QTimerEvent *e)
{

}

void Scene::resize(int w, int h)
{

}

