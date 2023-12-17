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
protected:
    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer indexBuffer;

    QOpenGLTexture *texture;
    QVector3D center;
    QMatrix4x4 modelMatrix;
public:
    SimpleObject3D();
    ~SimpleObject3D();
    SimpleObject3D(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &textureImage);
    virtual void draw(QOpenGLShaderProgram &sp, QOpenGLFunctions *functions);
    virtual void scale(qreal multiplicator);
    void init(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &textureImage);
    void setTexture(QString path);
    virtual void moveTo(QVector3D position);
    virtual void moveTo(qreal x, qreal y, qreal z);
    virtual void moveAt(QVector3D position);
    virtual void moveAt(qreal x, qreal y, qreal z);
    virtual void rotate(qreal deg);
};

#endif // SimpleObject3D_H
