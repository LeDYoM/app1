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
    if (setActive())
    {
        vertexLocation_ = program->attributeLocation("aVertexPosition");
        program->enableAttributeArray(vertexLocation_);
        colorLocation_ = program->attributeLocation("aVertexColor");
        program->enableAttributeArray(colorLocation_);

        //glVertexAttribPointer(vertexLocation_, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), 0);


    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
//    int texcoordLocation = shader->Program()->attributeLocation("a_texcoord");
//    shader->Program()->enableAttributeArray(texcoordLocation);
//    glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    // Offset for color
//    offset = sizeof(QVector3D) + sizeof(QVector2D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
//    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(unsigned short), 0);
        return true;
    }
    return false;

}

bool Shader::setActive()
{
    return program->bind();
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
