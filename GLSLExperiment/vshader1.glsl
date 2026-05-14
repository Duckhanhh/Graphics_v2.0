#version 400

in vec4 vPosition;
in vec4 vColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec4 color;

void main()
{
    gl_Position = uProjection * uView * uModel * vPosition;
    color = vColor;
}