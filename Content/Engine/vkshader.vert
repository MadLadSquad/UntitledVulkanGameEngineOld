#version 450

layout(location = 0) out vec3 fragmentColour;

// Vertex positions
vec3 positions[3] = vec3[]
(
    vec3(0.0, -0.4, 0.0),
    vec3(0.4, 0.4, 0.0),
    vec3(-0.4, 0.4, 0.0)
);

// Vertex colours
vec3 colours[3] = vec3[]
(
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
);

void main()
{
    // Set the position to the current vertex index
    gl_Position = vec4(positions[gl_VertexIndex], 1.0);
    fragmentColour = colours[gl_VertexIndex];
}