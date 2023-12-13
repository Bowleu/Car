#ifndef CAR_H
#define CAR_H
#include <QVector3D>
#include <limits>
#include <cmath>
#include <QMap>
#include "object3d.h"

class Car : public Object3D
{
    QMap<QString, SimpleObject3D*> objects;
    float speed = 0.0f;
    float angle = 1.0f;
public:
    Car();
    Car(QString pathToFile);
    ~Car();
    bool rayTriangleIntersect(QVector3D orig, QVector3D dir, QVector3D v0, QVector3D v1, QVector3D v2);
    void setRotation(float angle);
    void moveForward(float speed);
};

#endif // CAR_H
