#version 450

layout(location = 0) in vec3 fragmentColour;
layout(location = 0) out vec4 outputColour;

void main()
{
    outputColour = vec4(fragmentColour, 1.0);
}