#include "demoscene1.h"
#include <QMouseEvent>
#include "meshobject.h"
#include "meshbuffer.h"
#include "camera.h"

static MeshObject *cubeObject=0;

DemoScene1::DemoScene1(SceneManager *scnManager)
    :Scene(scnManager),angularSpeed(0.0)
{
}

void DemoScene1::mousePressEvent(QMouseEvent *e)
{
    mousePressPosition = QVector2D(e->localPos());
}

void DemoScene1::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}


void DemoScene1::timerEvent(QTimerEvent *e)
{
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
        cubeObject->setRotation(rotation);
    }
}

void DemoScene1::onCreate()
{
    createCamera<Camera>();
    getCamera()->setZNear(3.0);
    getCamera()->setZFar(7.0);
    getCamera()->setAngle(45.0);

    cubeObject = getCamera()->create<MeshObject>();
    cubeObject->setMBuffer(MeshBuffer::createCubeGeometry(QVector3D(1.0f,1.0f,1.0f)));
//    cubeObject->setMBuffer(new MeshBuffer(geometryCreator->createCubeGeometry(QVector3D(2,2,2)),Shader::defaultShader()));
    cubeObject->setPosition(Vector3D(0.0f,0.0f, -5.0f));
}
