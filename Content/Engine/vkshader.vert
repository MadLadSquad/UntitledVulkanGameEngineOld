#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 col;
layout(location = 0) out vec4 fragcol;

void main()
{
    // Set the position to the current vertex index
    gl_Position = vec4(pos, 1.0);
    fragcol = col;
}