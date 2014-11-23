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

