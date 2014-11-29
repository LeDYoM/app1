#ifndef SHADER_H
#define SHADER_H

#include "config.h"

class QGLShaderProgram;

class Shader
{
public:
    static bool InitShaders();
    static inline Shader *defaultShader() { return shaders[0]; }

    inline void setMVMatrixPointer(const QMatrix4x4 &mvMatrix) { program->setUniformValue("uMVMatrix", mvMatrix); }
    inline void setProjectionMatrixPointer(const QMatrix4x4 &pMatrix) { program->setUniformValue("uPMatrix", pMatrix); }
    inline GLShaderProgram *Program() { return program; }

    virtual bool storeAttributeIndices();
    bool setActive();

    inline int vertexLocation() const { return vertexLocation_; }
    inline int colorLocation() const { return colorLocation_; }

private:
    Shader();

    static QList<Shader*> shaders;
    static Shader *fromSourceFile(const String &,const String &);
    static Shader *fromSourceCode(const String &,const String &);
    QGLShaderProgram *program;
    int vertexLocation_;
    int colorLocation_;
};

#endif // SHADER_H
