#ifndef MESHBUFFER_H
#define MESHBUFFER_H

#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include "vdata.h"

class QOpenGLBuffer;

class MeshBuffer
{
public:
    MeshBuffer();

    static MeshBuffer *createCubeGeometry(const QVector3D &size);

    int addVertex(const QVector3D &nv)
    {
        vc.positions.push_back(nv);
        return vc.positions.size();
    }

    int setVertices(const QVector<QVector3D> &nv)
    {
        vc.positions = nv;
        return vc.positions.size();
    }

    int addColor(const QColor &nc)
    {
        vc.colors.push_back(nc);
        return vc.colors.size();
    }

    int setColors(const QVector<QColor> &nc)
    {
        vc.colors = nc;
        return vc.colors.size();
    }

    int addtextureCoordinate(const QVector2D &ntc)
    {
        vc.textureCoordinates.push_back(ntc);
        return vc.textureCoordinates.size();
    }

    int setTextureCoordinates(const QVector<QVector2D> &ntc)
    {
        vc.textureCoordinates = ntc;
        return vc.textureCoordinates.size();
    }

    int addIndex(const unsigned short &ni)
    {
        vc.indices.push_back(ni);
        return vc.indices.size();
    }

    int setIndices(const QVector<unsigned short> &ni)
    {
        vc.indices = ni;
        return vc.indices.size();
    }

    inline bool isReady() const { return isReady_; }
    bool bind();

    inline VertexCommunication *getVC() { return &vc; }
protected:
    VertexCommunication vc;
private:
    bool isReady_;
};

#endif // MESHBUFFER_H
