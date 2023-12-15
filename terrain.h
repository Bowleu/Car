#ifndef TERRAIN_H
#define TERRAIN_H
#include "vertexdata.h"
#include "object3d.h"
#include <QVector>

class Terrain : public Object3D
{
    int size = 3;
    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer indexBuffer;
    QOpenGLTexture *texture;
    QVector <VertexData> vertData;
    QMatrix4x4 modelMatrix;
public:

    Terrain();
    //void draw(QOpenGLShaderProgram &sp, QOpenGLFunctions *functions);
    int getSize();
    QVector<VertexData> getVertData();
    ~Terrain();
};

#endif // TERRAIN_H
