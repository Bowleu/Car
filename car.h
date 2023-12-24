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
    int width;
    int rayTriangleIntersect(QVector3D v0, QVector3D v1, QVector3D v2);
public:
    Car();
    Car(QString pathToFile);
    ~Car();
    int checkRayIntersection(Terrain &terrain);
    void moveForward(float speed);
    void setWidth(float roadWidth);
};

#endif // CAR_H
