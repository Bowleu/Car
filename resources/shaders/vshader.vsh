attribute highp vec4 aPosition;
attribute highp vec2 aTexCoord;
attribute highp vec3 aNormal;

uniform highp mat4 uProjectionMatrix;
uniform highp mat4 uViewMatrix;
uniform highp mat4 uModelMatrix;

varying highp vec2 vTexCoord;
varying highp vec3 vPosition;
varying highp vec3 vNormal;

void main(void)
{
    mat4 mvMatrix = uViewMatrix * uModelMatrix;

    gl_Position = vec4(uProjectionMatrix * mvMatrix * aPosition);

    vPosition = mvMatrix * aPosition;
    vNormal = normalize(vec3(mvMatrix * vec4(aNormal, 0.0)));
    vTexCoord = aTexCoord;
}
