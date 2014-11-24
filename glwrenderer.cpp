#include "glwrenderer.h"
#include <QMouseEvent>
#include <math.h>
#include "meshobject.h"
#include "shader.h"
#include "vdata.h"
#include "camera.h"
#include "meshbuffer.h"
#include "scene.h"
#include "scenemanager.h"
#include <QGLContext>
#include "renderer.h"
#include "log.h"

GLWRenderer::GLWRenderer(QGLFormat &format, QWidget *parent) :
    QGLWidget(format,parent), angularSpeed(0)
{
    renderer = Renderer::create(context(),this);
    scnManager = new SceneManager(this);
}

GLWRenderer::~GLWRenderer()
{
    //    deleteTexture(texture);
}

void GLWRenderer::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
    scnManager->mousePressEvent(e);
}

void GLWRenderer::mouseReleaseEvent(QMouseEvent *e)
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

    scnManager->mouseReleaseEvent(e);

}

static MeshObject *cubeObject;
static Scene *scene;
static Camera *camera;

void GLWRenderer::timerEvent(QTimerEvent *e)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
        cubeObject->setRotation(rotation);
    }
    // Update scene
//    updateGL();

    scnManager->timerEvent(e);

}

void GLWRenderer::initializeGL()
{
    renderer->initialize();

//    initTextures();

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);

    scnManager = new SceneManager(renderer);
    scene = scnManager->createScene<Scene>();
    camera = scene->createCamera<Camera>();
    camera->setZNear(3.0);
    camera->setZFar(7.0);
    camera->setAngle(45.0);

    cubeObject = camera->create<MeshObject>();
    cubeObject->setMBuffer(MeshBuffer::createCubeGeometry(QVector3D(1.0f,1.0f,1.0f)));
//    cubeObject->setMBuffer(new MeshBuffer(geometryCreator->createCubeGeometry(QVector3D(2,2,2)),Shader::defaultShader()));
    cubeObject->setPosition(Vector3D(0.0f,0.0f, -5.0f));

    scnManager->set_activeScene(scene);
}

void GLWRenderer::initTextures()
{
    return;
    /*
    // Load cube.png image
    glEnable(GL_TEXTURE_2D);
    texture = bindTexture(QImage(":/cube.png"));

    // Set nearest filtering mode for texture minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set bilinear filtering mode for texture magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    */
}

void GLWRenderer::resizeGL(int w, int h)
{
    renderer->setSize(w,h);

    qreal aspect = qreal(w) / qreal(h ? h : 1);
    camera->setRatio(aspect);
}

void GLWRenderer::paintGL()
{
    scnManager->Render(renderer);
    update();
}
