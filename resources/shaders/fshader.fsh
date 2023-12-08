uniform sampler2D uTexture;
varying highp vec2 vTexCoord;
varying highp vec3 vPosition;
varying highp vec3 vNormal;

void main(void)
{
    //vNormal = vec3(0.0, 0.0, 0.0);
    //gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    gl_FragColor = texture2D(uTexture, vTexCoord);
}
