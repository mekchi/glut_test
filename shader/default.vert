
#version 130

uniform mat4 projection;
uniform mat4 modelview;

in vec4 vertex;

void main()
{
    gl_Position =  projection * modelview * vertex;
}
