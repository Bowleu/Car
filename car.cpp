#include "car.h"
Car::Car()
{

}
void Car::setSpeed(float speed)
{
    Object3D::moveAt(QVector3D(0, 0, speed));
}
float Car::rayTriangleIntersect(QVector3D v0, QVector3D v1, QVector3D v2)
{

    // orig и dir задают начало и направление луча. v0, v1, v2 - вершины треугольника.
    // Функция возвращает расстояние от начала луча до точки пересечения или 0.
    QVector3D orig = QVector3D(Object3D::getPosition().x(),0,Object3D::getPosition().z());
    qDebug() << orig
    QVector3D dir = QVector3D(0,-1,0);
    dir.normalize();
    //qDebug() << dir;
    //QVector3D dir = QVector3D(sqrt(2)/2,-sqrt(2)/2,0);
    QVector3D e1 = v1 - v0;
    QVector3D e2 = v2 - v0;
    // Вычисление вектора нормали к плоскости
    QVector3D pvec = QVector3D::crossProduct(dir, e2);
    float det = QVector3D::dotProduct(e1, pvec);

    // Луч параллелен плоскости
    if (det < 1e-8 && det > -1e-8) return false;

    float inv_det = 1 / det;
    QVector3D tvec = orig - v0;
    float u = QVector3D::dotProduct(tvec, pvec) * inv_det;
    if (u < 0 || u > 1) return false;

    QVector3D qvec = QVector3D::crossProduct(tvec, e1);
    float v = QVector3D::dotProduct(dir, qvec) * inv_det;
    if (v < 0 || u + v > 1) return false;

    // Треугольник за в протитвоположной стороне от направления луча
    if(QVector3D::dotProduct(e2, qvec) * inv_det < 0) return false;

    return  QVector3D::dotProduct(e2, qvec) * inv_det;
}
float Car::checkRayIntersection(Terrain terrain){
    int size = terrain.getSize();
    float distance = 0;
    QVector<QVector3D> vertCoords = terrain.getVertCoords();
    for(int i = 0; i<size; i+=1){
        //qDebug() << size << vertCoords[i] << vertCoords[i+1] << vertCoords[i+2];
        distance = rayTriangleIntersect(vertCoords[i],vertCoords[i+1],vertCoords[i+2]);
        if (distance != 0) return distance;
    }
    return false;
}
void Car::setWidth(float roadWidth){
    scale(((roadWidth/3)/216));
    qDebug() << "((roadWidth/3)/216);" << ((roadWidth/3.0f)/216.0f);// 216 - ширина машины
}
Car::~Car(){
    for (auto pair : objects.toStdMap()) {
        delete pair.second;
    }
}
