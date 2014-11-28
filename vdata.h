#ifndef VDATA_H
#define VDATA_H

#include <QVector2D>
#include <QVector3D>
#include <QColor>
#include <QVector>
#include <QOpenGLBuffer>

struct VertexCommunication
{
    QVector<QVector3D> positions;
    QVector<unsigned short> indices;
    QVector<QColor> colors;
    QVector<QVector2D> textureCoordinates;
    QOpenGLBuffer *vbo[4];
};

#endif // VDATA_H
