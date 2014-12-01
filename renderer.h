#ifndef RENDERER_H
#define RENDERER_H

#include "config.h"
#include <QGLFunctions>
#include <QObject>
#include <QVector>
#include "vdata.h"

class Shader;
class MeshBuffer;
class QGLContext;
class QOpenGLBuffer;
class QGLShaderProgram;

class Renderer : public QObject, protected QGLFunctions
{
    Q_OBJECT

private:
    Renderer(QGLContext *context_, QGLWidget *parent_=0);
public:

    virtual ~Renderer();
    static Renderer *create(QGLContext *context_, QGLWidget *parent_=0);
    static Renderer *Instance();
    bool initialize();
    void Clear();
    void Render(MeshBuffer *obj);

    void setProjection(const Matrix4x4 &projection_);
    void setModelView(const Matrix4x4 &modelView_);
    void prepareNewFrame();
    void setSize(int w, int h);

    bool createBuffers(MeshBuffer *);
    QGLShaderProgram *newShaderProgram();
private:
    void setShaderMatrices(Shader *shader);
    Matrix4x4 projection;
    Matrix4x4 modelView;
    QGLContext *rcontext;
    Shader *activeShader;

    static Renderer *instance;


};

#endif // RENDERER_H
