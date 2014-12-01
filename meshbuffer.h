#ifndef MESHBUFFER_H
#define MESHBUFFER_H

#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include "vdata.h"

class QOpenGLBuffer;
class RenderableVAO;

class MeshBuffer
{
public:
    MeshBuffer();

    static MeshBuffer *createCubeGeometry(const QVector3D &size);

    int addVertex(const Simple3DVector &nv)
    {
        positions.push_back(nv);
        return positions.size();
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
        colors.push_back(nc);
        return colors.size();
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
        textureCoordinates.push_back(ntc);
        return textureCoordinates.size();
    }

    int setTextureCoordinates(const QVector<QVector2D> &ntc)
    {
        textureCoordinates = ntc;
        return textureCoordinates.size();
    }

    int addIndex(const unsigned short &ni)
    {
        indices.push_back(ni);
        return indices.size();
    }

    int setIndices(const QVector<unsigned short> &ni)
    {
        indices = ni;
        return indices.size();
    }

    inline bool isReady() const { return isReady_; }
    bool bind();

    inline const Simple3DVector *Positions() const { return positions.constData(); }
    inline const unsigned short *Indices() const { return indices.constData(); }
    inline const SimpleRGBAColor *Colors() const { return colors.constData(); }
    inline const QVector2D *TextureCoordinates() const { return textureCoordinates.constData(); }
    inline int PositionsSize() const { return positions.size(); }
    inline int IndicesSize() const { return indices.size(); }
    inline int ColorsSize() const { return colors.size(); }
    inline int textureCoordinatesSize() const { return textureCoordinates.size(); }

    RenderableVAO *rvao;

protected:
    QVector<Simple3DVector> positions;
    QVector<unsigned short> indices;
    QVector<SimpleRGBAColor> colors;
    QVector<QVector2D> textureCoordinates;

private:
    bool isReady_;
};

#endif // MESHBUFFER_H
