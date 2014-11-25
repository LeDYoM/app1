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

    DEF_Q_PROPERTY(Renderer*,renderer)
    DEF_Q_PROPERTY(SceneManager*,scnManager)

public:
    explicit GLWRenderer(QGLFormat &format, QWidget *parent = 0);
    virtual ~GLWRenderer();

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void timerEvent(QTimerEvent *e);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initTextures();

private:
    QBasicTimer timer;
};

#endif // GLWRENDERER_H
