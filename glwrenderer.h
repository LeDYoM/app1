#ifndef GLWRENDERER_H
#define GLWRENDERER_H

#include "config.h"
#include "properties.h"
#include <QGLWidget>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>

class Renderer;
class SceneManager;

class GLWRenderer : public QGLWidget
{
    Q_OBJECT

    DEF_PROPERTY(Renderer*,renderer,Renderer)
    DEF_PROPERTY(SceneManager*,scnManager,SceneManager)

public:
    explicit GLWRenderer(QGLFormat &format, QWidget *parent = 0);
    virtual ~GLWRenderer();

    bool event(QEvent *);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initTextures();

private:
    QBasicTimer timer;
};

#endif // GLWRENDERER_H
