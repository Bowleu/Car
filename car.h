#ifndef CAR_H
#define CAR_H
#include <QVector3D>
#include <limits>
#include <cmath>
#include <QMap>
#include "object3d.h"
#include "simpleObject3d.h"
#include "terrain.h"

class Car : public Object3D
{
    QMap<QString, SimpleObject3D*> objects;
    float speed = 0.0f;
    float angle = 0.0f;
public:
    Car();
    Car(QString pathToFile);
    ~Car();
    float checkRayIntersection(Terrain terrain);
    float rayTriangleIntersect(QVector3D v0, QVector3D v1, QVector3D v2);
    //void setRotation(float angle);
    void setSpeed(float speed);
    void setWidth(float roadWidth);
};

#endif // CAR_H
