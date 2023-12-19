#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QTimer>
#include <QVector3D>
#include <QFile>
#include <QOpenGLContext>
#include "camera.h"
#include "vertexdata.h"
#include "object3d.h"
#include "simpleObject3d.h"
#include "car.h"

class Scene : public QOpenGLWidget
{
    Q_OBJECT
    Camera *mainCamera;
    Camera *cam1;
    Camera *cam2;
    Camera *cam3;
    QOpenGLShaderProgram sp;
    QTimer *updateTimer;
    QTimer *rayTimer;
    QVector <Object3D *> objects;
    SimpleObject3D *cube;
    Car car;
    Terrain terrain;
    const float tickDuration = 10.0f;
    const float rayCheckDuration = 100.0f;
public:
    bool cam_idle_state = 1;
    bool idle_state = 1;
    bool speedup = 0;
    int activeCam = 1;
    Scene();
    Scene(QWidget *parent);
    ~Scene();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void initShaders();
    void initCube(float width);
private slots:
    void throwRay();
    void updateScene();
};

#endif // SCENE_H
