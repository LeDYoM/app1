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
    QGLWidget(format,parent)
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
    scnManager->mousePressEvent(e);
}

void GLWRenderer::mouseReleaseEvent(QMouseEvent *e)
{
    scnManager->mouseReleaseEvent(e);
}


static Scene *scene;

void GLWRenderer::timerEvent(QTimerEvent *e)
{
    scnManager->timerEvent(e);
}

void GLWRenderer::initializeGL()
{
    renderer->initialize();

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);

    scene = scnManager->createScene<Scene>();
    scene->onCreate();
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
    scnManager->resize(w,h);
}

void GLWRenderer::paintGL()
{
    scnManager->Render(renderer);
    update();
}
