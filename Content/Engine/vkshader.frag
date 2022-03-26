#version 450

layout(location = 0) out vec4 outputColour;
layout(location = 0) in vec4 fragCol;

void main()
{
    outputColour = fragCol;
}