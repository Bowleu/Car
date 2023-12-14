#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <QString>
#include <QMap>
#include "simpleObject3d.h"

class Object3D
{
    QMap<QString, SimpleObject3D*> objects;
    qreal rotation;
    QVector3D center;
public:
    Object3D();
    Object3D(QString pathToFile);
    void loadObjectFromFile(QString pathToFile);
    SimpleObject3D* getObject(QString name);
    void rotate(qreal degrees); // Вокруг оси y
    void scale(qreal miltiplicator);
    void moveTo(QVector3D position);
    void moveTo(qreal x, qreal y, qreal z);
    void moveAt(QVector3D position);
    void moveAt(qreal x, qreal y, qreal z);
    void draw(QOpenGLShaderProgram &sp, QOpenGLFunctions *functions);
    QVector3D getPosition();
    qreal getRotation();
    ~Object3D();
};

#endif // OBJECT3D_H
