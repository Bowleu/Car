#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QElapsedTimer>
#include <QVector3D>
#include <QFile>
#include <QOpenGLContext>
#include "camera.h"
#include "vertexdata.h"
#include "object3d.h"
#include "simpleObject3d.h"

class Scene : public QOpenGLWidget
{
    Q_OBJECT
public:
    Scene();
    Scene(QWidget *parent);
    ~Scene();
protected:

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initShaders();
    void initCube(float width);
private:
    Camera *mainCamera;
    QOpenGLShaderProgram sp;
    QElapsedTimer *eltimer;
    QVector <Object3D *> objects;
    SimpleObject3D *cube;

};

#endif // SCENE_H
