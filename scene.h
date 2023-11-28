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
#include "camera.h"

struct VertexData {
    VertexData() {
    }
    VertexData(QVector3D p, QVector2D c, QVector3D n) : position(p), coords(c), normal(n)
    {
    }
    QVector3D position;
    QVector2D coords;
    QVector3D normal;

};

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
    QMatrix4x4 MVP;
    QOpenGLShaderProgram sp;
    QOpenGLTexture *texture;
    QOpenGLBuffer arrayBuffer;
    QOpenGLBuffer indexBuffer;
    QElapsedTimer *eltimer;
};

#endif // SCENE_H
