#include "car.h"
#include <QtMath>
Car::Car()
{
    width = 216;
}
void Car::moveForward(float speed)
{
    QVector3D direction(speed * qSin(rotation * 3.14159 / 180), 0, speed * qCos(rotation * 3.14159 / 180));
    moveAt(direction);
}
int Car::rayTriangleIntersect(QVector3D v0, QVector3D v1, QVector3D v2) // Алгоритм Меллера-Трумбора
{

    // orig и dir задают начало и направление луча. v0, v1, v2 - вершины треугольника.
    // Функция возвращает расстояние от начала луча до точки пересечения или 0.

    QVector3D orig = QVector3D(getPosition().x(), getPosition().y() + 60, getPosition().z());
    QVector3D dir(qSin(rotation * 3.14159 / 180), -0.28, qCos(rotation * 3.14159 / 180));

    dir.normalize();
    QVector3D e1 = v1 - v0;
    QVector3D e2 = v2 - v0;
    // Вычисление вектора нормали к плоскости
    QVector3D pvec = QVector3D::crossProduct(dir, e2);
    float det = QVector3D::dotProduct(e1, pvec);

    // Луч параллелен плоскости
    if (det < 1e-8 && det > -1e-8) {
        return 0;
    }
    float inv_det = 1 / det;
    QVector3D tvec = orig - v0;
    float u = QVector3D::dotProduct(tvec, pvec) * inv_det;
    if (u < 0 || u > 1){
        return 0;
    }

    QVector3D qvec = QVector3D::crossProduct(tvec, e1);
    float v = QVector3D::dotProduct(dir, qvec) * inv_det;
    if (v < 0 || u + v > 1){
        return 0;
    }

    // Треугольник в протитвоположной стороне от направления луча
    if(QVector3D::dotProduct(e2, qvec) * inv_det < 0) return false;

    return QVector3D::dotProduct(e2, qvec) * inv_det;
}
int Car::checkRayIntersection(Terrain &terrain){
    QVector<QVector3D> vertCoords = terrain.getVertCoords();
    int distance;
    for(int i = 0; i < vertCoords.size() - 2; i += 3){
        distance = rayTriangleIntersect(vertCoords[i], vertCoords[i+1], vertCoords[i+2]);
        if (distance){
            return distance;
        }
    }
    return distance;
}
void Car::setWidth(float w){
    scale(w / width);
    width = w;
}
Car::~Car(){
}
