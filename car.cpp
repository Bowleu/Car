#include "car.h"
Car::Car()
{

}
void Car::moveForward(float speed)
{
    Object3D::moveAt(QVector3D(0, 0, speed));
}
bool Car::rayTriangleIntersect(
    QVector3D orig, const QVector3D dir,
    QVector3D v0, QVector3D v1, QVector3D v2)
{
    // compute the plane's normal
    QVector3D v0v1 = v1 - v0;
    QVector3D v0v2 = v2 - v0;
    // no need to normalize
    QVector3D N = v0v1.crossProduct(v0v1, v0v2); // N
    //float area2 = N.length();

    // Step 1: finding P

    // check if the ray and plane are parallel.
    float NdotRayDirection = QVector3D::dotProduct(N, dir);
    if (fabs(NdotRayDirection) < std::numeric_limits<double>::epsilon()) // almost 0
        return false; // they are parallel, so they don't intersect!

    // compute d parameter using equation 2
    float d = -QVector3D::dotProduct(N,v0);

    // compute t (equation 3)
    float t;
    t = -(QVector3D::dotProduct(orig, N) + d) / NdotRayDirection;
    // check if the triangle is behind the ray
    if (t < 0)
        return false; // the triangle is behind

    // compute the intersection point using equation 1
    QVector3D P = orig + t * dir;
    qDebug() << "Intersection: " << P;
    // Step 2: inside-outside test
    QVector3D C; // vector perpendicular to triangle's plane

    // edge 0
    QVector3D edge0 = v1 - v0;
    QVector3D vp0 = P - v0;
    C = QVector3D::crossProduct(vp0,edge0);
    if (QVector3D::dotProduct(C,N) < 0){
        //qDebug() << "edge0";
        return false; // P is on the right side

    }
    // edge 1
    QVector3D edge1 = v2 - v1;
    QVector3D vp1 = P - v1;
    C = QVector3D::crossProduct(vp1,edge1);
    if (QVector3D::dotProduct(C,N) < 0){
        //qDebug() << "edge1";
        return false; // P is on the right side

    }

    // edge 2
    QVector3D edge2 = v0 - v2;
    QVector3D vp2 = P - v2;
    C = QVector3D::crossProduct(vp2,edge2);
    if (QVector3D::dotProduct(C,N) < 0){
        //qDebug() << "edge2";
        return false; // P is on the right side;
    }

    return true; // this ray hits the triangle
}
Car::~Car(){
    for (auto pair : objects.toStdMap()) {
        delete pair.second;
    }
}
