#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

class Camera
{
    int fov;
    float aspect;
    float nearCut, farCut;
    QVector3D position;
    QVector3D viewOn;

    QMatrix4x4 view;
    QMatrix4x4 projection;
    QMatrix4x4 model;

    QMatrix4x4 MVP;

    void calcMVP();
public:
    Camera();
    Camera(QVector3D position, QVector3D viewOn, float near, float far, int fov, float aspect);

    void setPosition(QVector3D position);
    void setPosition(float x, float y, float z);

    void setViewOn(QVector3D viewOn);
    void setViewOn(float x, float y, float z);
    void setViewOn(float horAngle, float verAngle);

    void show(QOpenGLShaderProgram &sp);
};

#endif // CAMERA_H
