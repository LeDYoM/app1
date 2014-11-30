#include "renderer.h"
#include "shader.h"
#include "meshbuffer.h"
#include "vdata.h"
#include "scenemanager.h"
#include "log.h"

Renderer *Renderer::instance=0;

Renderer::Renderer(QGLContext *context_, QGLWidget *parent_):QObject(parent_),QGLFunctions(context_),rcontext(context_)
{

}

Renderer::~Renderer()
{

}

Renderer *Renderer::create(QGLContext *context_, QGLWidget *parent_)
{
    if (!instance)
    {
        instance = new Renderer(context_,parent_);
    }
    return instance;
}

Renderer *Renderer::Instance()
{
    return instance;
}


bool Renderer::initialize()
{
    initializeGLFunctions(rcontext);
    glClearColor(0,0,0,0);
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    prepareNewFrame();

    if (!Shader::InitShaders())
    {
        return false;
    }

    activeShader = Shader::defaultShader();

    return true;
}

void Renderer::prepareNewFrame()
{
    projection.setToIdentity();
    modelView.setToIdentity();

    Clear();
}

void Renderer::setSize(int w, int h)
{
    glViewport(0, 0, w, h);
}

bool Renderer::createBuffers(VertexCommunication *vc)
{
    Shader *shader = Shader::defaultShader();

    vc->vao = new QOpenGLVertexArrayObject();
    vc->vao->create();
    vc->vao->bind();

    shader->Program()->bind();
    vc->vbo[0] = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    vc->vbo[0]->create();
    vc->vbo[0]->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vc->vbo[0]->bind();
    vc->vbo[0]->allocate(vc->indices.constData(), vc->indices.size() * sizeof(GLushort));

    vc->vbo[1] = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vc->vbo[1]->create();
    vc->vbo[1]->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vc->vbo[1]->bind();
    vc->vbo[1]->allocate(vc->positions.constData(), vc->positions.size() * sizeof(Simple3DVector));
//    shader->Program()->setAttributeBuffer("aVertexPosition", GL_FLOAT, 0, 3, 0);
    activeShader->Program()->setAttributeArray("aVertexPosition",0,3,sizeof(Simple3DVector));

    vc->vbo[2] = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vc->vbo[2]->create();
    vc->vbo[2]->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vc->vbo[2]->bind();
    vc->vbo[2]->allocate(vc->colors.constData(), vc->colors.size() * sizeof(SimpleRGBAColor));

    activeShader->Program()->setAttributeArray("aVertexColor",0,4,sizeof(SimpleRGBAColor));

    activeShader->Program()->enableAttributeArray("aVertexPosition");
    activeShader->Program()->enableAttributeArray("aVertexColor");

//    shader->Program()->setAttributeBuffer("aVertexColor", GL_FLOAT, 0, 4, 0);

    /*
        QOpenGLBuffer vertexColorBuffer(QOpenGLBuffer::VertexBuffer);
        vertexColorBuffer.create();
        vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
        vertexColorBuffer.bind();
        vertexColorBuffer.allocate(vertexColors, 9 * sizeof(float));
    glGenBuffers(2, vc->vbos);

    glBindBuffer(GL_ARRAY_BUFFER, vc->vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, vc->positions.size() * sizeof(QVector3D), vc->positions.constData(), GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vc->vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vc->indices.size() * sizeof(GLushort), vc->indices.constData(), GL_STATIC_DRAW);
    */
    vc->vao->release();
    activeShader->Program()->release();
    return true;
}

QGLShaderProgram *Renderer::newShaderProgram()
{
    return new QGLShaderProgram(rcontext,this);
}

void Renderer::Clear()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(MeshBuffer *obj)
{
    obj->getVC()->vao->bind();
    activeShader->Program()->bind();

    setShaderMatrices(activeShader);

    glDrawElements(GL_TRIANGLES, obj->getVC()->indices.size(), GL_UNSIGNED_SHORT, 0);
    obj->getVC()->vao->release();
}

void Renderer::setProjection(const Matrix4x4 &projection_)
{
    projection = projection_;
}

void Renderer::setModelView(const Matrix4x4 &modelView_)
{
    modelView = modelView_;
}

void Renderer::setShaderMatrices(Shader *shader)
{
    // Set modelview-projection matrix
    shader->setMVMatrixPointer(modelView);
    shader->setProjectionMatrixPointer(projection);
}
