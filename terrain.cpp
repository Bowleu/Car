#include "terrain.h"

Terrain::Terrain()
{
    //vertData = ...
}
int Terrain::getSize(){
    return size;
}
QVector<VertexData *> Terrain::getVertData(){
    return vertData;
}
Terrain::~Terrain()
{

}
