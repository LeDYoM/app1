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
private:
    Shader();

    static QList<Shader*> shaders;
    static Shader *fromSource(const String &vShaderFile,const String &fShaderFile);

    QGLShaderProgram *program;
    int vertexLocation_;
};

#endif // SHADER_H
