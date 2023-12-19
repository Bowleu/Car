#include "camera.h"
#include <QtMath>

void Camera::calcMVP()
{

    projection.setToIdentity();
    projection.perspective(fov, aspect, nearCut, farCut);

    // Матрица проеции, определяет угол обзора, ближнюю и дальнюю плоскости отсечения (дальность видимости)


    QVector3D zVec = viewOn - position;
    zVec.normalize();
    QVector3D upVec = {0, 1, 0};
    QVector3D xVec = QVector3D::crossProduct(zVec, upVec);
    QVector3D yVec = QVector3D::crossProduct(xVec, zVec);
    yVec.normalize();
    view = QMatrix4x4(xVec.x(), yVec.x(), -zVec.x(), 0,
                       xVec.y(), yVec.y(), -zVec.y(), 0,
                       xVec.z(), yVec.z(), -zVec.z(), 0,
                       -QVector3D::dotProduct(xVec, position), -QVector3D::dotProduct(yVec, position), QVector3D::dotProduct(zVec, position), 1);

    view = view.transposed();

    // Видовая матрица, определяет положение камеры, направление, вертикальное направление мира

}

Camera::Camera()
{
    fov = 45;
    aspect = (float) 900 / 400;
    nearCut = 0.1f;
    farCut = 10.0f;
    position = {0, 0, 0};
    viewOn = {0, 0, -1};
    calcMVP();
}

Camera::Camera(QVector3D position, QVector3D viewOn, float n, float f, int fov, float aspect)
{
    this->position = position;
    this->viewOn = viewOn;
    this->nearCut = n;
    this->farCut = f;
    this->fov = fov;
    this->aspect = aspect;

    calcMVP();
}

void Camera::setPosition(QVector3D position)
{
    this->position = position;
    calcMVP();
}

void Camera::setPosition(float x, float y, float z)
{
    position = {x, y, z};
    calcMVP();
}

void Camera::setPosition(Object3D &object, float x, float y, float z)
{
    position = object.getPosition() + QVector3D(x, y, z);
    calcMVP();
}

void Camera::setViewOn(QVector3D viewOn)
{
    this->viewOn= viewOn;
    calcMVP();
}

void Camera::setViewOn(float x, float y, float z)
{
    viewOn = {x, y, z};
    calcMVP();
}

void Camera::setViewOn(float horAngle, float vertAngle)
{
    viewOn = {position.x() + (float) qSin(horAngle) * (float) qCos(vertAngle), position.x() + (float) qSin(vertAngle), position.z() + (float) qCos(horAngle) * (float) qCos(vertAngle)};
    calcMVP();
}

void Camera::setViewOn(Object3D &object) {
    viewOn = object.getPosition();
    calcMVP();
}
void Camera::setFOV(float f) {
    fov = f;
    calcMVP();
}
void Camera::show(QOpenGLShaderProgram &sp)
{
    sp.setUniformValue("uProjectionMatrix", projection);
    sp.setUniformValue("uViewMatrix", view);
}
