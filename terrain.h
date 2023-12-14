#ifndef TERRAIN_H
#define TERRAIN_H
#include "vertexdata.h"
#include <QVector>

class Terrain
{
    int size;
    QVector <VertexData *> vertData;

public:
    Terrain();
    int getSize();
    QVector<VertexData *>getVertData();
    ~Terrain();
};

#endif // TERRAIN_H
