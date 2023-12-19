#ifndef TERRAIN_H
#define TERRAIN_H
#include "vertexdata.h"
#include "object3d.h"
#include <QVector>

class Terrain : public SimpleObject3D
{
    float r1;
    float r2;
    float roadWidth;
    QVector <QVector3D> vertCoords;
public:

    Terrain();
    //void draw(QOpenGLShaderProgram &sp, QOpenGLFunctions *functions);
    int getSize();
    QVector<QVector3D> getVertCoords();
    void loadObjectFromFile(QString path);
    float getRoadWidth();
    void scale(qreal multiplicator);
    ~Terrain();
    Terrain(QString pathToObj, QString pathToTexture);
};

#endif // TERRAIN_H
