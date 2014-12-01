#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include "properties.h"
#include "sceneobject.h"
#include <QObject>

class MeshBuffer;
class RenderableVAO;

class MeshObject : public SceneObject
{
public:
    explicit MeshObject(SceneObject *parent_);

    inline void setMBuffer(MeshBuffer *mbuffer_) { mBuffer = mbuffer_; }
protected:
    void Render(Renderer *renderer);
private:
    MeshBuffer *mBuffer;
    RenderableVAO *vao;
};

#endif // MESHOBJECT_H
