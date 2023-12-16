#include "terrain.h"
#include <QFile>

Terrain::Terrain() : SimpleObject3D()
{
    vertData.append(VertexData(QVector3D(500, 1000, 600),QVector2D(0.0, 1.0),QVector3D(0.0, 0.0, -1.0)));
    vertData.append(VertexData(QVector3D(500, -50, 600),QVector2D(0.0, 0.0),QVector3D(0.0, 0.0, -1.0)));
    vertData.append(VertexData(QVector3D(-500, -50, 600),QVector2D(1.0, 0.0),QVector3D(0.0, 0.0, -1.0)));

}


int Terrain::getSize(){
    return size;
}
QVector<VertexData> Terrain::getVertData(){
    return vertData;
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
                }
            }
        }
    }
    center = QVector3D(0, 0, 0);
    objFile.close();
    init(vertexes, indexes, QImage(":/textures/tex.jpg"));
}

Terrain::~Terrain()
{

}
