#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "config.h"
#include "childrencontainer.h"

class Renderer;

class SceneObject : public QObject, public ChildrenContainer<SceneObject>
{
    Q_OBJECT
public:
    SceneObject(SceneObject *parent_=0);

    READONLYPROPERTY(SceneObject *,parent,Parent)

    SIMPLEPROPERTY(Vector3D,position,Position,setPosition)
    SIMPLEPROPERTY(Vector3D,scale,Scale,setScale)
    SIMPLEPROPERTY(Quaternion,rotation,Rotation,setRotation)

public:
    template <typename T> T* create()
    {
        T *temp = new T(this);
        _children.push_back(temp);
        return temp;
    }

    inline const Matrix4x4 &LocalTransformation() const { return localTransformation; }
    inline const Matrix4x4 &GlobalTransformation() const { return globalTransformation; }

    virtual int RenderTree(Renderer *renderer);

protected:
    virtual void Render(Renderer *renderer) = 0;
    virtual void updateLocalTransformation();
    virtual void updateGlobalTransformation();
    void updateTransformations();

private:
    Matrix4x4 localTransformation;
    Matrix4x4 globalTransformation;
};

#endif // SCENEOBJECT_H
