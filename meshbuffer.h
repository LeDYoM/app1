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

    int addVertex(const Simple3DVector &nv)
    {
        vc.positions.push_back(nv);
        return vc.positions.size();
    }

    int addVertices(const QVector<QVector3D> &nv)
    {
        for (int i=0;i<nv.size()-1;++i)
        {
            addVertex(nv[i]);
        }
        return addVertex(nv[nv.size()-1]);
    }

    int addVertices(const QVector<Simple3DVector> &nv)
    {
        for (int i=0;i<nv.size()-1;++i)
        {
            addVertex(nv[i]);
        }
        return addVertex(nv[nv.size()-1]);
    }

    int addColor(const SimpleRGBAColor &nc)
    {
        vc.colors.push_back(nc);
        return vc.colors.size();
    }

    int addColors(const SimpleRGBAColor &nc,int numCopies)
    {
        for (int i=0;i<numCopies-1;++i)
        {
            addColor(nc);
        }

        return addColor(nc);
    }

    int setColors(const QVector<QColor> &nc)
    {
        for (int i=0;i<nc.size()-1;++i)
        {
            addColor(nc[i]);
        }
        return addColor(nc[nc.size()-1]);
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
