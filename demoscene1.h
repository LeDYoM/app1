#ifndef DEMOSCENE1_H
#define DEMOSCENE1_H

#include "scene.h"

class DemoScene1 : public Scene
{
public:
    DemoScene1(SceneManager *scnManager_);

    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void timerEvent(QTimerEvent *e);
    virtual void onCreate();

protected:
    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;

};

#endif // DEMOSCENE1_H
