#include "scene.h"
#include <QtMath>

Scene::Scene()
{

}

Scene::Scene(QWidget *parent) : QOpenGLWidget(parent)
{
    eltimer = new QElapsedTimer;
    eltimer->start();
}

Scene::~Scene()
{
    for (int i = 0; i < objects.size(); i++)
        delete objects[i];
}

void Scene::initializeGL() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glViewport(0,0,500,500);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_3D);

    initShaders();
    initCube(1.0);
    //objects.append(new Object3D(":/models/saratoga.obj"));
    car.loadObjectFromFile(":/models/saratoga.obj");
}

void Scene::resizeGL(int w, int h)
{
    float aspect = (float) w / h;
    mainCamera = new Camera(QVector3D(-400, 300.25, 300),
                              QVector3D(0, 0, 0),
                              0.1f,
                              2500.0f,
                              45,
                              aspect);
}

void Scene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sp.bind();

    if(cam_idle_state){
        mainCamera->setPosition(-155 + 700 * qSin(eltimer->elapsed() / 30 % 360 * 3.14159 / 180), 200, -55 + 700 * qCos(eltimer->elapsed() / 30 % 360 * 3.14159 / 180));
    }
    if(!idle_state){
        //mainCamera->setPosition(50,500,0); тут машина растягивается
        mainCamera->setPosition(-800,400,-800);
        car.moveForward(10);
        car.rotate(1);

    }
    mainCamera->show(sp);
    qDebug() << car.getPosition();
    qDebug() << car.rayTriangleIntersect(car.getPosition(),QVector3D(0,0,1),QVector3D(-1500, 250, 150*3),QVector3D(-1500, -50, 150*3),QVector3D(150, -50, 150*3));
    cube->draw(sp, context()->functions());
    /*for (int i = 0; i < objects.size(); i++) {
        objects[i]->rotate(1);
        objects[i]->moveAt(QVector3D(0, 0, 10));
        qDebug() << objects[0]->position();
        objects[i]->draw(sp, context()->fun(ctions());
    }*/

    car.draw(sp, context()->functions());
    initCube(300);
    //qDebug() << cube->modelMatrix;

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

  /*  vertexes.append(VertexData(QVector3D(-halfWidth, halfWidth, halfWidth), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
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

    vertexes.append(VertexData(QVector3D(halfWidth, halfWidth+100, halfWidth*3), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(halfWidth, -halfWidth+100, halfWidth*3), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-halfWidth, halfWidth+100, halfWidth*3), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-halfWidth, -halfWidth+100, halfWidth*3), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));*/
    vertexes.append(VertexData(QVector3D(1500, 250, 150*3), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(1500, -50, 150*3), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-150, -50, 150*3), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

    QVector <GLuint> indexes;
    for (int i = 0; i < 3; i += 3) {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }
    cube = new SimpleObject3D(vertexes, indexes, QImage(":/textures/tex.jpg"));
    //cube->moveTo(QVector3D(-10.5, 0.0, 10.0));
}

