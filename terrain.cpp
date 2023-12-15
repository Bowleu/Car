#include "terrain.h"

Terrain::Terrain()
{
    vertData.append(VertexData(QVector3D(500, 1000, 600),QVector2D(0.0, 1.0),QVector3D(0.0, 0.0, -1.0)));
    vertData.append(VertexData(QVector3D(500, -50, 600),QVector2D(0.0, 0.0),QVector3D(0.0, 0.0, -1.0)));
    vertData.append(VertexData(QVector3D(-500, -50, 600),QVector2D(1.0, 0.0),QVector3D(0.0, 0.0, -1.0)));
}

/*void Terrain::draw(QOpenGLShaderProgram &sp, QOpenGLFunctions *functions)
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
*/
int Terrain::getSize(){
    return size;
}
QVector<VertexData> Terrain::getVertData(){
    return vertData;
}

Terrain::~Terrain()
{

}
