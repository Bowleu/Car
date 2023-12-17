#ifndef TERRAIN_H
#define TERRAIN_H
#include "vertexdata.h"
#include "object3d.h"
#include <QVector>

class Terrain : public SimpleObject3D
{
    int size = 3;
    QVector <VertexData> vertData;
public:

    Terrain();
    //void draw(QOpenGLShaderProgram &sp, QOpenGLFunctions *functions);
    int getSize();
    QVector<VertexData> getVertData();
    void loadObjectFromFile(QString path);
    ~Terrain();
    Terrain(QString pathToObj, QString pathToTexture);
};

#endif // TERRAIN_H
