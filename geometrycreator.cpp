#include "geometrycreator.h"
#include "vdata.h"
#include <QVector2D>
#include <QVector3D>
#include <QQuaternion>

GeometryCreator::GeometryCreator()
{
    initializeGLFunctions();
}
/*
BasicGeometry *GeometryCreator::createCubeGeometry(const QVector3D &size)
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices[] = {
        // Vertex data for face 0
        VertexData(QVector3D(-0.5f, -0.5f,  0.5f), QVector2D(0.0f, 0.0f),QColor(255,255,255,255)),  // v0
        VertexData(QVector3D( 0.5f, -0.5f,  0.5f), QVector2D(0.33f, 0.0f),QColor(255,255,255,255)), // v1
        VertexData(QVector3D(-0.5f,  0.5f,  0.5f), QVector2D(0.0f, 0.5f),QColor(255,255,255,255)),  // v2
        VertexData(QVector3D( 0.5f,  0.5f,  0.5f), QVector2D(0.33f, 0.5f),QColor(255,255,255,255)), // v3

        // Vertex data for face 1
        VertexData(QVector3D( 0.5f, -0.5f,  0.5f), QVector2D( 0.0f, 0.5f),QColor(255,255,255,255)), // v4
        VertexData(QVector3D( 0.5f, -0.5f, -0.5f), QVector2D(0.33f, 0.5f),QColor(255,255,255,255)), // v5
        VertexData(QVector3D( 0.5f,  0.5f,  0.5f), QVector2D(0.0f, 1.0f),QColor(255,255,255,255)),  // v6
        VertexData(QVector3D( 0.5f,  0.5f, -0.5f), QVector2D(0.33f, 1.0f),QColor(255,255,255,255)), // v7


        // Vertex data for face 2
        VertexData(QVector3D( 0.5f, -0.5f, -0.5f), QVector2D(0.66f, 0.5f),QColor(255,255,255,255)), // v8
        VertexData(QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(1.0f, 0.5f),QColor(255,255,255,255)),  // v9
        VertexData(QVector3D( 0.5f,  0.5f, -0.5f), QVector2D(0.66f, 1.0f),QColor(255,255,255,255)), // v10
        VertexData(QVector3D(-0.5f,  0.5f, -0.5f), QVector2D(1.0f, 1.0f),QColor(255,255,255,255)),  // v11

        // Vertex data for face 3
        VertexData(QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.66f, 0.0f),QColor(255,255,255,255)), // v12
        VertexData(QVector3D(-0.5f, -0.5f,  0.5f), QVector2D(1.0f, 0.0f),QColor(255,255,255,255)),  // v13
        VertexData(QVector3D(-0.5f,  0.5f, -0.5f), QVector2D(0.66f, 0.5f),QColor(255,255,255,255)), // v14
        VertexData(QVector3D(-0.5f,  0.5f,  0.5f), QVector2D(1.0f, 0.5f),QColor(255,255,255,255)),  // v15

        // Vertex data for face 4
        VertexData(QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.33f, 0.0f),QColor(255,255,255,255)), // v16
        VertexData(QVector3D( 0.5f, -0.5f, -0.5f), QVector2D(0.66f, 0.0f),QColor(255,255,255,255)), // v17
        VertexData(QVector3D(-0.5f, -0.5f,  0.5f), QVector2D(0.33f, 0.5f),QColor(255,255,255,255)), // v18
        VertexData(QVector3D( 0.5f, -0.5f,  0.5f), QVector2D(0.66f, 0.5f),QColor(255,255,255,255)), // v19

        // Vertex data for face 5
        VertexData(QVector3D(-0.5f,  0.5f,  0.5f), QVector2D(0.33f, 0.5f),QColor(255,255,255,255)), // v20
        VertexData(QVector3D( 0.5f,  0.5f,  0.5f), QVector2D(0.66f, 0.5f),QColor(255,255,255,255)), // v21
        VertexData(QVector3D(-0.5f,  0.5f, -0.5f), QVector2D(0.33f, 1.0f),QColor(255,255,255,255)), // v22
        VertexData(QVector3D( 0.5f,  0.5f, -0.5f), QVector2D(0.66f, 1.0f),QColor(255,255,255,255))  // v23
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    Mesh a(vertices,indices);
    GLuint vboIds[2];
    // Generate 2 VBOs
    glGenBuffers(2, vboIds);

    // Transfer vertex data to VBO 0
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(VertexData), vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 34 * sizeof(GLushort), indices, GL_STATIC_DRAW);

    BasicGeometry *tmp = new BasicGeometry(vboIds[0],vboIds[1]);
    return tmp;
}
*/
/*
BasicGeometry *GeometryCreator::createCubeGeometry(const QVector3D &size)
{
    VertexData vertices[] = {
        // Vertex data for Front face
        VertexData(QVector3D(-0.5f, -0.5f,  0.5f)*size),
        VertexData(QVector3D( 0.5f, -0.5f,  0.5f)*size),
        VertexData(QVector3D( 0.5f,  0.5f,  0.5f)*size),
        VertexData(QVector3D(-0.5f,  0.5f,  0.5f)*size),

        // Vertex data for Back Face
        VertexData(QVector3D(-0.5f, -0.5f, -0.5f)*size),
        VertexData(QVector3D(-0.5f,  0.5f, -0.5f)*size),
        VertexData(QVector3D( 0.5f,  0.5f, -0.5f)*size),
        VertexData(QVector3D( 0.5f, -0.5f, -0.5f)*size),

        // Vertex data for Top Face
        VertexData(QVector3D(-0.5f,  0.5f, -0.5f)*size),
        VertexData(QVector3D(-0.5f,  0.5f,  0.5f)*size),
        VertexData(QVector3D( 0.5f,  0.5f,  0.5f)*size),
        VertexData(QVector3D( 0.5f,  0.5f, -0.5f)*size),

        // Vertex data for Bottom Face
        VertexData(QVector3D(-0.5f, -0.5f, -0.5f)*size),
        VertexData(QVector3D( 0.5f, -0.5f, -0.5f)*size),
        VertexData(QVector3D( 0.5f, -0.5f,  0.5f)*size),
        VertexData(QVector3D(-0.5f, -0.5f,  0.5f)*size),

        // Vertex data for Right Face
        VertexData(QVector3D( 0.5f, -0.5f, -0.5f)*size),
        VertexData(QVector3D( 0.5f,  0.5f, -0.5f)*size),
        VertexData(QVector3D( 0.5f,  0.5f,  0.5f)*size),
        VertexData(QVector3D( 0.5f, -0.5f,  0.5f)*size),

        // Vertex data for Left Face
        VertexData(QVector3D(-0.5f,  -0.5f, -0.5f)*size),
        VertexData(QVector3D(-0.5f,  -0.5f,  0.5f)*size),
        VertexData(QVector3D(-0.5f,   0.5f,  0.5f)*size),
        VertexData(QVector3D(-0.5f,   0.5f, -0.5f)*size)
    };

    GLushort indices[] = {
        0, 1, 2,      0, 2, 3,    // Front face
        4, 5, 6,      4, 6, 7,    // Back face
        8, 9, 10,     8, 10, 11,  // Top face
        12, 13, 14,   12, 14, 15, // Bottom face
        16, 17, 18,   16, 18, 19, // Right face
        20, 21, 22,   20, 22, 23  // Left face
    };

    GLuint vboIds[2];
    // Generate 2 VBOs
    glGenBuffers(2, vboIds);

    // Transfer vertex data to VBO 0
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(VertexData), vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLushort), indices, GL_STATIC_DRAW);

    BasicGeometry *tmp = new BasicGeometry(vboIds[0],24, vboIds[1], 36);
    return tmp;
}
*/
