#include "meshbuffer.h"
#include "log.h"
#include "renderer.h"
#include "vdata.h"

MeshBuffer::MeshBuffer():isReady_(false)
{
}

MeshBuffer *MeshBuffer::createCubeGeometry(const QVector3D &size)
{

    QVector<Simple3DVector> _vertices = {
        // Vertex data for Front face
        QVector3D(-0.5f, -0.5f,  0.5f)*size,
        QVector3D( 0.5f, -0.5f,  0.5f)*size,
        QVector3D( 0.5f,  0.5f,  0.5f)*size,
        QVector3D(-0.5f,  0.5f,  0.5f)*size,

        // Vertex data for Back Face
        QVector3D(-0.5f, -0.5f, -0.5f)*size,
        QVector3D(-0.5f,  0.5f, -0.5f)*size,
        QVector3D( 0.5f,  0.5f, -0.5f)*size,
        QVector3D( 0.5f, -0.5f, -0.5f)*size,

        // Vertex data for Top Face
        QVector3D(-0.5f,  0.5f, -0.5f)*size,
        QVector3D(-0.5f,  0.5f,  0.5f)*size,
        QVector3D( 0.5f,  0.5f,  0.5f)*size,
        QVector3D( 0.5f,  0.5f, -0.5f)*size,

        // Vertex data for Bottom Face
        QVector3D(-0.5f, -0.5f, -0.5f)*size,
        QVector3D( 0.5f, -0.5f, -0.5f)*size,
        QVector3D( 0.5f, -0.5f,  0.5f)*size,
        QVector3D(-0.5f, -0.5f,  0.5f)*size,

        // Vertex data for Right Face
        QVector3D( 0.5f, -0.5f, -0.5f)*size,
        QVector3D( 0.5f,  0.5f, -0.5f)*size,
        QVector3D( 0.5f,  0.5f,  0.5f)*size,
        QVector3D( 0.5f, -0.5f,  0.5f)*size,

        // Vertex data for Left Face
        QVector3D(-0.5f, -0.5f, -0.5f)*size,
        QVector3D(-0.5f, -0.5f,  0.5f)*size,
        QVector3D(-0.5f,  0.5f,  0.5f)*size,
        QVector3D(-0.5f,  0.5f, -0.5f)*size
    };

    QVector<unsigned short> _indices = {
        0, 1, 2,      0, 2, 3,    // Front face
        4, 5, 6,      4, 6, 7,    // Back face
        8, 9, 10,     8, 10, 11,  // Top face
        12, 13, 14,   12, 14, 15, // Bottom face
        16, 17, 18,   16, 18, 19, // Right face
        20, 21, 22,   20, 22, 23  // Left face
    };

    MeshBuffer *meshb = new MeshBuffer();
    meshb->vc.indices = _indices;
    meshb->addVertices(_vertices);

    meshb->bind();

    return meshb;
}

bool MeshBuffer::bind()
{
    if (vc.indices.size() < 1 || vc.positions.size() < 1)
    {
        DEBUG("Indices and vertices are required");
        return false;
    }

    if (vc.colors.size() < vc.positions.size())
    {
        DEBUG("Incresing color array with defaults");
        addColors(SimpleRGBAColor(1.0f,1.0f,1.0f,1.0f),vc.positions.size() - vc.colors.size());
    }

    Renderer::Instance()->createBuffers(&vc);
    return true;
}
