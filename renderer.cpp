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
    vc->vbo[0] = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vc->vbo[0]->create();
    vc->vbo[0]->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vc->vbo[0]->bind();
    vc->vbo[0]->allocate(vc->positions.constData(), vc->positions.size() * sizeof(QVector3D));

    vc->vbo[1] = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    vc->vbo[1]->create();
    vc->vbo[1]->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vc->vbo[1]->bind();
    vc->vbo[1]->allocate(vc->indices.constData(), vc->indices.size() * sizeof(GLushort));

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
    return true;
}

QGLShaderProgram *Renderer::newShaderProgram()
{
    return new QGLShaderProgram(rcontext,this);
}

void Renderer::Clear()
{
    rcontext->makeCurrent();
    // Clear color and depth buffer
    glClearColor(1.0,.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(MeshBuffer *obj)
{
    obj->getVC()->vbo[0]->bind();
    obj->getVC()->vbo[1]->bind();
//    glBindBuffer(GL_ARRAY_BUFFER, obj->getVC()->vbos[0]);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->getVC()->vbos[1]);

    RenderShader(activeShader);

    glDrawElements(GL_TRIANGLES, obj->getVC()->indices.size(), GL_UNSIGNED_SHORT, 0);
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

void Renderer::RenderShader(Shader *shader)
{
    // Offset for position
//    quintptr offset = 0;

    //shader->setActive();
    setShaderMatrices(shader);
    // Use texture unit 0 which contains cube.png
    //program.setUniformValue("texture", 0);

    // Tell OpenGL programmable pipeline how to locate vertex position data
//    int vertexLocation = shader->Program()->attributeLocation("aVertexPosition");
//    shader->Program()->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(shader->vertexLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), 0);

    // Offset for texture coordinate
//    offset += sizeof(QVector3D);

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
}
