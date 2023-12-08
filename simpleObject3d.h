#ifndef SimpleObject3D_H
#define SimpleObject3D_H

#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "vertexdata.h"

class SimpleObject3D
{
    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer indexBuffer;
    QMatrix4x4 modelMatrix;
    QOpenGLTexture *texture;
    QVector3D center;
public:
    SimpleObject3D();
    ~SimpleObject3D();
    SimpleObject3D(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &textureImage);
    void draw(QOpenGLShaderProgram &sp, QOpenGLFunctions *functions);
    void scale(qreal multiplicator);
    void init(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &textureImage);
    void moveTo(QVector3D position);
    void moveTo(qreal x, qreal y, qreal z);
    void moveAt(QVector3D position);
    void moveAt(qreal x, qreal y, qreal z);
    void rotate(float deg);
};

#endif // SimpleObject3D_H
