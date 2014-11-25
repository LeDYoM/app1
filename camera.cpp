#include "camera.h"
#include "scene.h"
#include "renderer.h"

Camera::Camera(Scene *parent_)
    :QObject(parent_)
{
    projection.setToIdentity();
}

void Camera::Render(Renderer *renderer)
{
    // Reset projection
    projection.setToIdentity();

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    //const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    setZNear(3.0);
    setZFar(7.0);

    // Set perspective projection
    projection.perspective(angle, ratio, zNear, zFar);

    renderer->setProjection(projection);

    for (auto it=_children.begin();it!=_children.end();++it)
    {
        (*it)->RenderTree(renderer);
    }
}

void Camera::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    setRatio(aspect);
}
