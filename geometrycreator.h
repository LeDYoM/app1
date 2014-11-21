#ifndef GEOMETRYCREATOR_H
#define GEOMETRYCREATOR_H

#include <QVector3D>
#include <QGLFunctions>

class BasicGeometry;

class GeometryCreator : protected QGLFunctions
{
public:
    GeometryCreator();

    BasicGeometry *createCubeGeometry(const QVector3D &size);
};

#endif // GEOMETRYCREATOR_H
