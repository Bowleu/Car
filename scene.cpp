#include "scene.h"
#include <QtMath>

Scene::Scene()
{

}

Scene::Scene(QWidget *parent) : QOpenGLWidget(parent), texture(0), indexBuffer(QOpenGLBuffer::IndexBuffer)
{
    eltimer = new QElapsedTimer;
    eltimer->start();
}

Scene::~Scene()
{

}

void Scene::initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0,0,500,500);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);

    initShaders();
    initCube(1.0f);
}

void Scene::resizeGL(int w, int h)
{
    float aspect = (float) w / h;
    mainCamera = new Camera(QVector3D(1, 1.25, 3),
                              QVector3D(0, 0, 0),
                              0.1f,
                              20.0f,
                              45,
                              aspect);
}

void Scene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind(0);

    sp.bind();

    sp.setUniformValue("qt_Texture0", 0);

    arrayBuffer.bind();

    int offset = 0;

    int vertLoc = sp.attributeLocation("qt_Vertex");
    sp.enableAttributeArray(vertLoc);
    sp.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texLoc = sp.attributeLocation("qt_MultiTexCoord0");
    sp.enableAttributeArray(texLoc);
    sp.setAttributeBuffer(texLoc, GL_FLOAT, offset, 2, sizeof(VertexData));

    indexBuffer.bind();

    int size = indexBuffer.size();

    QMatrix4x4 model;
    model.setToIdentity();
    //model.rotate(eltimer->elapsed() / 30 % 360, 0, 1, 0);
    sp.setUniformValue("qt_ModelMatrix", model);

    mainCamera->setPosition(2.5 * qSin(eltimer->elapsed() / 30 % 360 * 3.14159 / 180), 1.25, 2.5 * qCos(eltimer->elapsed() / 30 % 360 * 3.14159 / 180));

    mainCamera->show(sp);

    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
}

void Scene::initShaders()
{
    if (!sp.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader.vsh"))
        qDebug() << "VShader err";
    if (!sp.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader.fsh"))
        qDebug() << "FShader err";
    if (!sp.link())
        qDebug() << "Link err";
}

void Scene::initCube(float width)
{
    float halfWidth = width / 2.0f;
    QVector <VertexData> vertexes;

    vertexes.append(VertexData(QVector3D(-halfWidth, halfWidth, halfWidth), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-halfWidth, -halfWidth, halfWidth), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(halfWidth, halfWidth, halfWidth), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(halfWidth, -halfWidth, halfWidth), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));


    vertexes.append(VertexData(QVector3D(halfWidth, halfWidth, halfWidth), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(halfWidth, -halfWidth, halfWidth), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(halfWidth, halfWidth, -halfWidth), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(halfWidth, -halfWidth, -halfWidth), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(halfWidth, halfWidth, halfWidth), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(halfWidth, halfWidth, -halfWidth), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-halfWidth, halfWidth, halfWidth), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-halfWidth, halfWidth, -halfWidth), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-halfWidth, halfWidth, -halfWidth), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-halfWidth, -halfWidth, -halfWidth), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-halfWidth, halfWidth, halfWidth), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-halfWidth, -halfWidth, halfWidth), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-halfWidth, -halfWidth, halfWidth), QVector2D(0.0, 1.00), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-halfWidth, -halfWidth, -halfWidth), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(halfWidth, -halfWidth, halfWidth), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(halfWidth, -halfWidth, -halfWidth), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));

    vertexes.append(VertexData(QVector3D(halfWidth, halfWidth, -halfWidth), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(halfWidth, -halfWidth, -halfWidth), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-halfWidth, halfWidth, -halfWidth), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-halfWidth, -halfWidth, -halfWidth), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

    QVector <GLuint> indexes;
    for (int i = 0; i < 24; i += 4) {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }

    arrayBuffer.create();
    arrayBuffer.bind();
    arrayBuffer.allocate(vertexes.constData(), vertexes.size() * sizeof(VertexData));
    arrayBuffer.release();

    indexBuffer.create();
    indexBuffer.bind();
    indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    indexBuffer.release();

    texture = new QOpenGLTexture(QImage(":/textures/tex.jpg").mirrored());

    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

