#ifndef RENDERABLEVAO_H
#define RENDERABLEVAO_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class RenderableVAO
{
public:
    RenderableVAO();

    QOpenGLBuffer *vbo[4];
    QOpenGLVertexArrayObject *vao;

};

#endif // RENDERABLEVAO_H
