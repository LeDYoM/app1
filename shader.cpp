#include "shader.h"
#include <QGLShaderProgram>
#include "renderer.h"

List<Shader*> Shader::shaders;

bool Shader::InitShaders()
{
    shaders.push_back(fromSource(":/vshader",":/fshader"));
    return shaders.size() == 1;
}

Shader *Shader::fromSource(const String &vShaderFile, const String &fShaderFile)
{
    bool control = true;
    Shader *tempShader = new Shader();
    tempShader->program = Renderer::Instance()->newShaderProgram();

    control &= tempShader->program->addShaderFromSourceFile(QGLShader::Vertex, vShaderFile);
    control &= tempShader->program->addShaderFromSourceFile(QGLShader::Fragment, fShaderFile);
    control &= tempShader->program->link();
    control &= tempShader->program->bind();

    return control ? tempShader : 0;
}

Shader::Shader()
{
}
