#include "shader.h"
#include <QGLShaderProgram>
#include "renderer.h"

List<Shader*> Shader::shaders;

bool Shader::InitShaders()
{
    shaders.push_back(fromSource(":/vshader",":/fshader"));
    return shaders.size() == 1;
}

bool Shader::storeAttributeIndices()
{
    if (setActive())
    {
        vertexLocation_ = program->attributeLocation("aVertexPosition");
        program->enableAttributeArray(vertexLocation_);
        //glVertexAttribPointer(vertexLocation_, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), 0);


    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
//    int texcoordLocation = shader->Program()->attributeLocation("a_texcoord");
//    shader->Program()->enableAttributeArray(texcoordLocation);
//    glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    // Offset for color
//    offset = sizeof(QVector3D) + sizeof(QVector2D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
//    int colorLocation = shader->Program()->attributeLocation("aVertexColor");
//    shader->Program()->enableAttributeArray(colorLocation);
//    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(unsigned short), 0);
        return true;
    }
    return false;

}

bool Shader::setActive()
{
    return program->bind();
}

Shader *Shader::fromSource(const String &vShaderFile, const String &fShaderFile)
{
    bool control = true;
    Shader *tempShader = new Shader();
    tempShader->program = Renderer::Instance()->newShaderProgram();

    control &= tempShader->program->addShaderFromSourceFile(QGLShader::Vertex, vShaderFile);
    control &= tempShader->program->addShaderFromSourceFile(QGLShader::Fragment, fShaderFile);
    control &= tempShader->program->link();

    control &= tempShader->storeAttributeIndices();

    return control ? tempShader : 0;
}

Shader::Shader()
{

}
