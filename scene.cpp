#include "scene.h"
#include "renderer.h"
#include "camera.h"
#include "scenemanager.h"

Scene::Scene(SceneManager *scnManager_)
    :QObject(scnManager_)
{
}

int Scene::RenderScene(Renderer *renderer)
{
    camera->Render(renderer);
    return 0;
}

void Scene::Render(Renderer *renderer)
{
}

