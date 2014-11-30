#include "shader.h"
#include <QGLShaderProgram>
#include "renderer.h"

List<Shader*> Shader::shaders;

bool Shader::InitShaders()
{
//    shaders.push_back(fromSourceFile(":/vshader",":/fshader"));
    shaders.push_back(fromSourceCode(
                          "attribute vec3 aVertexPosition;"
                          "attribute vec4 aVertexColor;"
                          "uniform mat4 uMVMatrix;"
                          "uniform mat4 uPMatrix;"
                          "varying vec4 vColor;"
                          "void main(void) {"
                          "    gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);"
                          "    vColor = aVertexColor;"
                          "}",

                          "varying vec4 vColor;"
                          "void main(void) {"
                          "    gl_FragColor = vColor;"
                          "}"
                          ));
    return shaders.size() == 1;
}

bool Shader::storeAttributeIndices()
{
    if (program->bind())
    {
/*
        vertexLocation_ = program->attributeLocation("aVertexPosition");
        program->enableAttributeArray(vertexLocation_);
        colorLocation_ = program->attributeLocation("aVertexColor");
        program->enableAttributeArray(colorLocation_);
*/
/*
        Program()->setAttributeArray("aVertexPosition",0,3,sizeof(Simple3DVector));
        Program()->enableAttributeArray("aVertexPosition");
        Program()->setAttributeArray("aVertexColor",0,4,sizeof(SimpleRGBAColor));
        Program()->enableAttributeArray("aVertexColor");
*/
        return true;
    }
    return false;

}

Shader *Shader::fromSourceCode(const String &vShader, const String &fShader)
{
    bool control = true;
    Shader *tempShader = new Shader();
    tempShader->program = Renderer::Instance()->newShaderProgram();

    control &= tempShader->program->addShaderFromSourceCode(QGLShader::Vertex, vShader);
    control &= tempShader->program->addShaderFromSourceCode(QGLShader::Fragment, fShader);
    control &= tempShader->program->link();

    control &= tempShader->storeAttributeIndices();

    return control ? tempShader : 0;
}

Shader *Shader::fromSourceFile(const String &vShaderFile, const String &fShaderFile)
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
