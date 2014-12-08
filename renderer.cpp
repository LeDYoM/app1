#include "renderer.h"
#include "shader.h"
#include "meshbuffer.h"
#include "vdata.h"
#include "scenemanager.h"
#include "log.h"
#include "renderablevao.h"

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

bool Renderer::createBuffers(MeshBuffer *mb)
{
    Shader *shader = Shader::defaultShader();

    mb->rvao = new RenderableVAO();
    mb->rvao->vao = new QOpenGLVertexArrayObject();
    mb->rvao->vao->create();
    mb->rvao->vao->bind();

    shader->Program()->bind();
    mb->rvao->vbo[0] = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    mb->rvao->vbo[0]->create();
    mb->rvao->vbo[0]->setUsagePattern(QOpenGLBuffer::StaticDraw);
    mb->rvao->vbo[0]->bind();
    mb->rvao->vbo[0]->allocate(mb->Indices(), mb->IndicesSize() * sizeof(GLushort));

    mb->rvao->vbo[1] = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    mb->rvao->vbo[1]->create();
    mb->rvao->vbo[1]->setUsagePattern(QOpenGLBuffer::StaticDraw);
    mb->rvao->vbo[1]->bind();
    mb->rvao->vbo[1]->allocate(mb->Positions(), mb->PositionsSize() * sizeof(Simple3DVector));
    activeShader->Program()->setAttributeArray("aVertexPosition",0,3,sizeof(Simple3DVector));

    mb->rvao->vbo[2] = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    mb->rvao->vbo[2]->create();
    mb->rvao->vbo[2]->setUsagePattern(QOpenGLBuffer::StaticDraw);
    mb->rvao->vbo[2]->bind();
    mb->rvao->vbo[2]->allocate(mb->Colors(), mb->ColorsSize() * sizeof(SimpleRGBAColor));

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
    mb->rvao->vao->release();
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
    obj->rvao->vao->bind();
    activeShader->Program()->bind();

    setShaderMatrices(activeShader);

    glDrawElements(GL_TRIANGLES, obj->IndicesSize(), GL_UNSIGNED_SHORT, 0);
    obj->rvao->vao->release();
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
