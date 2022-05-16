#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec3 normal;

layout(location = 0) out vec4 fragcol;
layout(location = 1) out vec2 fraguv;
layout(location = 2) out vec3 fragmentWorldPosition;
layout(location = 3) out vec3 fragmentNormalWorld;


layout(binding = 0) uniform VP
{
    mat4 view;
    mat4 projection;

    mat4 normalMatrix;
    mat4 inverseViewMatrix;

    vec4 lightPosition;
    vec4 lightColour;
    vec4 ambientLightColour;
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
    vec4 worldPosition = model.model * vec4(pos, 1.0);
    gl_Position = vp.projection * vp.view * worldPosition;

    fragmentNormalWorld = normalize((vp.normalMatrix * vec4(normal, 0.0)).xyz);
    fragmentWorldPosition = worldPosition.xyz;

    fragcol = col;
    fraguv = uv;
}