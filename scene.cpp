#include "scene.h"
#include "renderer.h"
#include "camera.h"
#include "scenemanager.h"

Scene::Scene(SceneManager *scnManager_)
    :QObject(scnManager_),camera(0)
{
}

void Scene::Render(Renderer *renderer)
{
    if (camera)
    {
        camera->Render(renderer);
    }
}

bool Scene::event(QEvent *e)
{
    return QObject::event(e);
}
/*
void Scene::mousePressEvent(QMouseEvent *e)
{
}

void Scene::mouseReleaseEvent(QMouseEvent *e)
{
}


void Scene::timerEvent(QTimerEvent *e)
{
}
*/

void Scene::resize(int w, int h)
{
    camera->resizeGL(w,h);
}

void Scene::onCreate()
{
}
