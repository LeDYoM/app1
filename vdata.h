#ifndef VDATA_H
#define VDATA_H

#include <QVector2D>
#include <QVector3D>
#include <QColor>
#include <QVector>
#include <QOpenGLBuffer>

struct Simple3DVector
{
    float x;
    float y;
    float z;

    Simple3DVector(const QVector3D &from)
    {
        x = from.x();
        y = from.y();
        z = from.z();
    }

    Simple3DVector(float x_=0.0f,float y_=0.0f,float z_=0.0f)
    {
        x = x_;
        y = y_;
        z = z_;
    }
};

struct SimpleRGBAColor
{
    float r;
    float g;
    float b;
    float a;

    SimpleRGBAColor(const QColor &from)
    {
        r = from.redF();
        g = from.greenF();
        b = from.blueF();
        a = from.alphaF();
    }

    SimpleRGBAColor(float r_=1.0f,float g_=1.0f,float b_=1.0f,float a_=1.0f)
    {
        r = r_;
        g = g_;
        b = b_;
        a = a_;
    }
};

struct VertexCommunication
{
    QVector<Simple3DVector> positions;
    QVector<unsigned short> indices;
    QVector<SimpleRGBAColor> colors;
    QVector<QVector2D> textureCoordinates;
    QOpenGLBuffer *vbo[4];
};

#endif // VDATA_H
