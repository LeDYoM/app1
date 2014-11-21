#include "config.h"
#include "sceneobject.h"
#include "renderer.h"

SceneObject::SceneObject(SceneObject *parent_)
    :QObject(parent_), parent(parent_),position(0.0f,0.0f,0.0f),scale(1.0f,1.0f,1.0f),rotation()
{
    localTransformation.setToIdentity();
    globalTransformation.setToIdentity();
}

int SceneObject::RenderTree(Renderer *renderer)
{
    int count(0);

    updateTransformations();

    Render(renderer);

    for (auto it=_children.begin();it!=_children.end();++it)
    {
        count += (*it)->RenderTree(renderer);
    }
    return count;
}

void SceneObject::updateLocalTransformation()
{
    localTransformation.setToIdentity();
    localTransformation.translate(position);
    localTransformation.rotate(rotation);
    localTransformation.scale(scale);
}

void SceneObject::updateGlobalTransformation()
{
    globalTransformation = parent ? parent->GlobalTransformation() * localTransformation : localTransformation;
}

void SceneObject::updateTransformations()
{
    updateLocalTransformation();
    updateGlobalTransformation();
}
