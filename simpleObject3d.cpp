#include "simpleObject3d.h"

SimpleObject3D::SimpleObject3D() : indexBuffer(QOpenGLBuffer::IndexBuffer), texture(0)
{

}

SimpleObject3D::SimpleObject3D(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &textureImage) :
    indexBuffer(QOpenGLBuffer::IndexBuffer), texture(0)
{
    init(vertData, indexes, textureImage);
}

void SimpleObject3D::draw(QOpenGLShaderProgram &sp, QOpenGLFunctions *functions)
{
    if (!vertexBuffer.isCreated() or !indexBuffer.isCreated())
        return;
    texture->bind(0);
    sp.setUniformValue("uTexture", 0);
    sp.setUniformValue("uModelMatrix", modelMatrix);

    vertexBuffer.bind();

    int offset = 0;

    int vertLoc = sp.attributeLocation("aPosition");
    sp.enableAttributeArray(vertLoc);
    sp.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texLoc = sp.attributeLocation("aTexCoord");
    sp.enableAttributeArray(texLoc);
    sp.setAttributeBuffer(texLoc, GL_FLOAT, offset, 2, sizeof(VertexData));

    offset += sizeof(QVector2D);

    indexBuffer.bind();

    int size = indexBuffer.size();

    sp.setUniformValue("uModelMatrix", modelMatrix);

    functions->glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

    vertexBuffer.release();
    indexBuffer.release();
    texture->release();
}

void SimpleObject3D::scale(qreal multiplicator)
{
    modelMatrix.scale(multiplicator);

}

void SimpleObject3D::init(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &textureImage) {
    if (vertexBuffer.isCreated())
        vertexBuffer.destroy();
    if (indexBuffer.isCreated())
        indexBuffer.destroy();
    if (texture != nullptr) {
        if (texture->isCreated()) {
            delete texture;
            texture = nullptr;
        }
    }
    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.allocate(vertData.constData(), vertData.size() * sizeof(VertexData));
    vertexBuffer.release();

    indexBuffer.create();
    indexBuffer.bind();
    indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    indexBuffer.release();

    texture = new QOpenGLTexture(textureImage.mirrored());
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);

    modelMatrix.setToIdentity();
    center = QVector3D(0, 0, 0);
}

void SimpleObject3D::setTexture(QString path)
{
    if (texture != nullptr) {
        if (texture->isCreated())
            texture->destroy();
    }
    texture = new QOpenGLTexture(QImage(path).mirrored());
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void SimpleObject3D::moveTo(QVector3D position)
{
    modelMatrix.setColumn(3, QVector4D(position,  modelMatrix.column(3).w()));
    center = QVector3D(modelMatrix.column(3).x(), modelMatrix.column(3).y(), modelMatrix.column(3).z());
}

void SimpleObject3D::moveTo(qreal x, qreal y, qreal z)
{
    QVector3D position(x, y, z);
    modelMatrix.setColumn(3, QVector4D(position,  modelMatrix.column(3).w()));
    center = QVector3D(modelMatrix.column(3).x(), modelMatrix.column(3).y(), modelMatrix.column(3).z());
}

void SimpleObject3D::moveAt(QVector3D position)
{
    QVector4D position4D = modelMatrix.column(3) + QVector4D(position, 0);
    modelMatrix.setColumn(3, position4D);
    center = QVector3D(modelMatrix.column(3).x(), modelMatrix.column(3).y(), modelMatrix.column(3).z());
}

void SimpleObject3D::moveAt(qreal x, qreal y, qreal z)
{
    QVector3D position(x, y, z);
    QVector4D position4D = modelMatrix.column(3) + QVector4D(position, 0);
    modelMatrix.setColumn(3, position4D);
    center = QVector3D(modelMatrix.column(3).x(), modelMatrix.column(3).y(), modelMatrix.column(3).z());;
}

void SimpleObject3D::rotate(qreal deg)
{
    modelMatrix.rotate(deg, 0, 1, 0);
}



SimpleObject3D::~SimpleObject3D() {
    if (vertexBuffer.isCreated())
        vertexBuffer.destroy();
    if (indexBuffer.isCreated())
        indexBuffer.destroy();
    if (texture != nullptr) {
        if (texture->isCreated())
            texture->destroy();
    }
}
