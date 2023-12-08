#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <QVector3D>
#include <QVector2D>

struct VertexData {
    VertexData() {
    }
    VertexData(QVector3D p, QVector2D c, QVector3D n) : position(p), coords(c), normal(n)
    {
    }
    QVector3D position;
    QVector2D coords;
    QVector3D normal;

};

#endif // VERTEXDATA_H
