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
    car.loadObjectFromFile(":/models/saratoga.obj");
    terrain.loadObjectFromFile(":/models/newroad1.obj");
    terrain.setTexture(":/textures/road.jpg");

    car.setWidth(terrain.getRoadWidth());
}

void Scene::resizeGL(int w, int h)
{
    float aspect = (float) w / h;
    mainCamera = new Camera(QVector3D(-400, 300.25, 300),
                              QVector3D(0, 0, 0),
                              0.1f,
                              10000.0f,
                              45,
                              aspect);
}

void Scene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sp.bind();
    //cube->draw(sp, context()->functions());
    car.draw(sp, context()->functions());
    terrain.SimpleObject3D::draw(sp, context()->functions());

    if(cam_idle_state){
        //mainCamera->setPosition(-155 + 700 * qSin(eltimer->elapsed() / 30 % 360 * 3.14159 / 180), 400, -55 + 700 * qCos(eltimer->elapsed() / 30 % 360 * 3.14159 / 180));
        mainCamera->setPosition(-300,200,500);
        car.moveTo(-200,0,0);
    }
    if(!idle_state){
        mainCamera->setPosition(-300,200,500);
        qDebug() << car.checkRayIntersection(terrain);
        //qDebug() << distanceToWall;
        car.setSpeed(3);
    }
    mainCamera->show(sp);


    //qDebug() << car.getPosition();

    /*for (int i = 0; i < objects.size(); i++) {
        objects[i]->rotate(1);
        objects[i]->moveAt(QVector3D(0, 0, 10));
        qDebug() << objects[0]->position();
        objects[i]->draw(sp, context()->fun(ctions());
    }*/

    //initCube(300);

    //qDebug() << cube->modelMatrix;
    //qDebug() << qCos(1) << cos(1*3.14159/180);
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
    vertexes.append(VertexData(QVector3D(500, 1000, 600), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(500, -50, 600), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-500, -50, 600), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-500, 1000, 600), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));

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

