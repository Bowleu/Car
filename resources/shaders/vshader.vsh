attribute highp vec4 qt_Vertex;
attribute highp vec4 qt_MultiTexCoord0;
uniform highp mat4 qt_ProjectionMatrix;
uniform highp mat4 qt_ViewMatrix;
uniform highp mat4 qt_ModelMatrix;
varying highp vec4 qt_TexCoord0;
varying highp mat4 qt_ModelViewProjectionMatrix;

void main(void)
{
    qt_ModelViewProjectionMatrix = qt_ProjectionMatrix * qt_ViewMatrix * qt_ModelMatrix;
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    qt_TexCoord0 = qt_MultiTexCoord0;
}
