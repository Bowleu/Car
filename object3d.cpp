#include "object3d.h"
#include <QFile>

Object3D::Object3D()
{

}

Object3D::Object3D(QString pathToFile) {
    loadObjectFromFile(pathToFile);
}

void Object3D::loadObjectFromFile(QString pathToFile) {
    rotation = 0;
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
    SimpleObject3D *object = nullptr;
    QImage texture;

    while (!input.atEnd()) {
        QString str = input.readLine();
        QStringList elements = str.split(" ", QString::SkipEmptyParts);

        if (elements.size() == 0) {
            continue;
        }
        else if (elements[0] == "o") { // Новый объект
            if (object != nullptr) {
                object->init(vertexes, indexes, texture);
            }
            if (elements[1] == "LowGlass")
                return;
            object = new SimpleObject3D;
            objects.insert(elements[1], object);
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
    object->init(vertexes, indexes, texture);
    center = QVector3D(0, 0, 0);
    objFile.close();
}

SimpleObject3D *Object3D::getObject(QString name)
{
    return objects[name];
}

void Object3D::rotate(qreal degrees)
{
    rotation += degrees;
    for (auto pair : objects.toStdMap()) {
        pair.second->rotate(degrees);
    }
}

void Object3D::scale(qreal multiplicator)
{
    for (auto pair : objects.toStdMap()) {
        pair.second->scale(multiplicator);
    }
}

void Object3D::moveTo(QVector3D position)
{
    for (auto pair : objects.toStdMap()) {
        pair.second->moveTo(position);
    }
    center = position;
}

void Object3D::moveTo(qreal x, qreal y, qreal z)
{
    QVector3D position(x, y, z);
    for (auto pair : objects.toStdMap()) {
        pair.second->moveTo(position);
    }
    center = position;
}

void Object3D::moveAt(QVector3D position)
{
    for (auto pair : objects.toStdMap()) {
        pair.second->moveAt(position);
    }
    QMatrix4x4 rotate;
    rotate.setToIdentity();
    rotate.rotate(rotation, 0, 1, 0);
    center += position * rotate;
}

void Object3D::moveAt(qreal x, qreal y, qreal z)
{
    QVector3D position(x, y, z);
    for (auto pair : objects.toStdMap()) {
        pair.second->moveAt(position);
    }
    QMatrix4x4 rotate;
    rotate.setToIdentity();
    rotate.rotate(rotation, 0, 1, 0);
    center += position * rotate;
}

void Object3D::draw(QOpenGLShaderProgram &sp, QOpenGLFunctions *functions)
{
    for (auto pair : objects.toStdMap()) {
        pair.second->draw(sp, functions);
    }
}

QVector3D Object3D::getPosition()
{
    return center;
}

Object3D::~Object3D()
{
    for (auto pair : objects.toStdMap()) {
        delete pair.second;
    }
}
