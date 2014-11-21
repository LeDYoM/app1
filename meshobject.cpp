#include "meshobject.h"
#include "meshbuffer.h"
#include "renderer.h"

MeshObject::MeshObject(SceneObject *parent_)
    :SceneObject(parent_), mBuffer(0)
{
}

void MeshObject::Render(Renderer *renderer)
{
    renderer->setModelView(GlobalTransformation());
    renderer->Render(mBuffer);
}
