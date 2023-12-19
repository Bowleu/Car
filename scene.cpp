#include "scene.h"
#include <QtMath>

Scene::Scene()
{

}

Scene::Scene(QWidget *parent) : QOpenGLWidget(parent)
{
    updateTimer = new QTimer;
    rayTimer = new QTimer;
    rayTimer->start(rayCheckDuration);
    updateTimer->start(tickDuration);
    connect(rayTimer, &QTimer::timeout, this, &Scene::throwRay);
    connect(updateTimer, &QTimer::timeout, this, &Scene::updateScene);
}
Scene::~Scene()
{
    for (int i = 0; i < objects.size(); i++)
        delete objects[i];
}

void Scene::initializeGL() {
    glClearColor(0.6f, 0.7f, 0.8f, 1.0f);
    glViewport(0,0,500,500);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_3D);

    initShaders();
    car.loadObjectFromFile(":/models/saratoga.obj");
    terrain.loadObjectFromFile(":/models/newroad1.obj");
    terrain.setTexture(":/textures/road.jpg");
    car.setWidth(terrain.getRoadWidth());
    rayTimer->start(100);                          // Машина дергается, потому что проверка раз в 100мс.
    car.moveTo(-200,0,0);
}

void Scene::resizeGL(int w, int h)
{
    float aspect = (float) w / h;
    cam1 = new Camera(QVector3D(-400, 100.25, 0),
                              QVector3D(0, 0, 0),
                              0.1f,
                              10000.0f,
                              45,
                              aspect);
    cam2 = new Camera(QVector3D(-400, 100.25, 0),
                              QVector3D(0, 0, 0),
                              0.1f,
                              10000.0f,
                              45,
                              aspect);
    cam3 = new Camera(QVector3D(-400, 100.25, 0),
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
    terrain.draw(sp, context()->functions());
    car.draw(sp, context()->functions());
    cam1->setPosition(car, -180, 150, -180);
    cam1->setViewOn(car);
    cam2->setPosition(car, -200 * qSin((car.getRotation() + 90) * 3.14159 / 180), 100, -200 * qCos((car.getRotation() + 90) * 3.14159 / 180));
    cam2->setViewOn(car);
    cam3->setPosition(-300,130,500);
    cam3->setFOV(-(qSqrt(qPow(car.getPosition().x()+150,2)+qPow(car.getPosition().z()-200,2)))/30+35);
    cam3->setViewOn(car);
    if(activeCam == 1){
        mainCamera = cam1;
    } else if(activeCam == 2){
        mainCamera = cam2;
    } else if(activeCam == 3){
        mainCamera = cam3;
    }
    mainCamera->show(sp);
    if(!idle_state){
        if(speedup) car.moveForward((20.0f/(1000/tickDuration))*10);
        else car.moveForward((20.0f/(1000/tickDuration))); //По умолчанию скорость 20 ед. р. (тик-каждый 10 мс. всего 1000мс в секуде).
    }
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


void Scene::updateScene(){
    update();
}
void Scene::throwRay()
{
    if (!car.checkRayIntersection(terrain))
        if (speedup) car.rotate(8);
        else car.rotate(4);
}

