#version 450
layout(location = 0) in vec4 fragCol;
layout(location = 1) in vec2 tex;

layout(set = 1, binding = 0) uniform sampler2D samplert;

layout(location = 0) out vec4 outputColour;

void main()
{
    outputColour = texture(samplert, tex) * fragCol;
}