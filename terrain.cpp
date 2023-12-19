#include "terrain.h"
#include <QFile>

Terrain::Terrain() : SimpleObject3D()
{
}

Terrain::Terrain(QString pathToObj, QString pathToTexture) {
    loadObjectFromFile(pathToObj);
    setTexture(pathToTexture);
}


int Terrain::getSize(){
    return size;
}
QVector<QVector3D> Terrain::getVertCoords(){
    return vertCoords;
}

void Terrain::loadObjectFromFile(QString pathToFile)
{
    QFile objFile(pathToFile);
    if (!objFile.exists()) {
        qDebug() << ".obj file not found.";
    }
    objFile.open(QIODevice::ReadOnly);
    QTextStream input(&objFile);

    QVector<QVector3D> coords;
    QVector<QVector2D> texCoords;
    QVector<QVector3D> normals;

    QVector <VertexData> vertexes;
    QVector <GLuint> indexes;
    QImage texture;

    while (!input.atEnd()) {
        QString str = input.readLine();
        QStringList elements = str.split(" ", QString::SkipEmptyParts);

        if (elements.size() == 0) {
            continue;
        }
        else if (elements[0] == "usemtl") {
            texture = QImage(":/textures/" + elements[1] + ".png");
        }
        else if (elements[0] == "v") {  // Координаты вершин
            coords.append(QVector3D(elements[1].toFloat(), elements[2].toFloat(), elements[3].toFloat()));
        }
        else if (elements[0] == "vt") { // Координаты текстур
            texCoords.append(QVector2D(elements[1].toFloat(), elements[2].toFloat()));
        }
        else if (elements[0] == "vn") { // Координаты текстур
            normals.append(QVector3D(elements[1].toFloat(), elements[2].toFloat(), elements[3].toFloat()));
        }
        else if (elements[0] == "f") { // Полигоны
            int polygons = elements.size() - 3;
            for (int i = 1; i <= polygons; i++) {
                QStringList vertInfo = elements[1].split("/");
                vertexes.append(VertexData(coords[vertInfo[0].toLong() - 1], texCoords[vertInfo[1].toLong() - 1], normals[vertInfo[2].toLong() - 1]));
                indexes.append(indexes.size());
                for (int j = i + 1; j <= i + 2; j++) {
                    QStringList vertInfo = elements[j].split("/");
                    vertexes.append(VertexData(coords[vertInfo[0].toLong() - 1], texCoords[vertInfo[1].toLong() - 1], normals[vertInfo[2].toLong() - 1]));
                    indexes.append(indexes.size());
                    vertCoords.append(QVector3D(qRound(coords[vertInfo[0].toLong() - 1].x()*1000.0f)/1000.0f,qRound(coords[vertInfo[0].toLong() - 1].y()*1000.0f)/1000.0f,qRound(coords[vertInfo[0].toLong() - 1].z()*1000.0f)/1000.0f));
                }
            }
        }
    }
    center = QVector3D(0, 0, 0);
    objFile.close();

    size = vertCoords.size();
    for(int i = 0; i < size; i++) qDebug() << vertCoords[i];
    init(vertexes, indexes, QImage(":/textures/tex.jpg"));
    float maxXZ = 0;
        for(int i = 0; i < size; i++){
        if(vertCoords[i].x()>r1){
            r1 = qRound(vertCoords[i].x()*1000.0f)/1000.0f;
            maxXZ = qRound(vertCoords[i].z()*1000.0f)/1000.0f;

        }
    }
    for(int i = 0; i < size; i++){
        if(vertCoords[i].z()==maxXZ){
            if(r2< vertCoords[i].x() && vertCoords[i].x() < r1) r2 = vertCoords[i].x();
        }
    }
    roadWidth = r1-r2;
    //for(int i = 0; i < size; i++) qDebug() << vertCoords[i];
    qDebug() << r1 << r2;

}
float Terrain::getRoadWidth(){
    return roadWidth;
}
Terrain::~Terrain()
{

}
