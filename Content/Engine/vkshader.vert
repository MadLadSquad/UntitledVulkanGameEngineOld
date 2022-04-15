#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec2 tex;

layout(location = 0) out vec4 fragcol;
layout(location = 1) out vec2 fragtex;

layout(binding = 0) uniform VP
{
    mat4 view;
    mat4 projection;
} vp;

//layout(binding = 1) uniform Model
//{
//    mat4 model;
//} model1;

layout(push_constant) uniform PushModel
{
    mat4 model;
} model;

void main()
{
    // Set the position to the current vertex index
    gl_Position = vp.projection * vp.view * model.model * vec4(pos, 1.0);
    fragcol = col;
    fragtex = tex;
}