#ifndef SCENE_H
#define SCENE_H

#include "config.h"
#include "sceneobject.h"
#include <QBasicTimer>

class SceneManager;
class Camera;
class Renderer;

class Scene : public QObject
{
    Q_OBJECT
public:
    explicit Scene(SceneManager *scnManager_);
    void resizeGL(int w, int h);
    void Render(Renderer *renderer);

public:
    template <typename T> T* createCamera()
    {
        Camera *temp = new T(this);
        camera = temp;
        return temp;
    }

    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void timerEvent(QTimerEvent *e);
    virtual void resize(int w, int h);
    virtual void onCreate();

private:
    Camera *camera;

    //QBasicTimer timer;

//    GLuint texture;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;

};

#endif // SCENE_H
