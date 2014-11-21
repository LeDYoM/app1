#ifndef CAMERA_H
#define CAMERA_H

#include "config.h"
#include "childrencontainer.h"
#include "sceneobject.h"

class Scene;
class Renderer;

class Camera : public QObject, public ChildrenContainer<SceneObject>
{
    Q_OBJECT

    SIMPLEPROTECTEDPROPERTY(float,zNear,ZNear,setZNear)
    SIMPLEPROTECTEDPROPERTY(float,zFar,ZFar,setZFar)
    SIMPLEPROPERTY(float,angle,Angle,setAngle)
    SIMPLEPROPERTY(float,ratio,Ratio,setRatio)

public:
    Camera(Scene *parent_);
    virtual void resizeGL(int w, int h);

    Matrix4x4 const& Projection() const { return projection; }

    template <class T>
    T *create()
    {
        T *temp = new T(0);
        _children.push_back(temp);
        return temp;
    }

protected:
    virtual void Render(Renderer *renderer);

    Matrix4x4 projection;
    friend class Scene;

};

#endif // CAMERA_H
