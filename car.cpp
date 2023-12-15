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
    QVector3D orig = QVector3D(Object3D::getPosition().x()+cos(Object3D::getRotation()*3.14159/180)*200,0,Object3D::getPosition().z()+sin(Object3D::getRotation()*3.14159/180)*200);
    QVector3D dir = QVector3D(sin(Object3D::getRotation()*3.14159/180),0,cos(Object3D::getRotation()*3.14159/180));
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
    QVector<VertexData> vertData = terrain.getVertData();
    for(int i = 0; i<size; i+=3){
        qDebug() << vertData[i].position << vertData[i+1].position<< vertData[i+2].position;
        distance = rayTriangleIntersect(vertData[i].position,vertData[i+1].position,vertData[i+2].position);
        if (distance != 0) return distance;
    }
    return false;
}
Car::~Car(){
    for (auto pair : objects.toStdMap()) {
        delete pair.second;
    }
}
