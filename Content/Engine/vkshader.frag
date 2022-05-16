#version 450
layout(location = 0) in vec4 fragCol;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 fragmentWorldPosition;
layout(location = 3) in vec3 fragmentNormalWorld;

layout(set = 1, binding = 0) uniform sampler2D samplert;

layout(location = 0) out vec4 outputColour;

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

void main()
{
    vec3 directionToLight = normalize(vp.lightPosition.xyz) - fragmentWorldPosition;
    vec3 specularLight = vec3(0.0);

    vec3 cameraPosWorld = vp.inverseViewMatrix[3].xyz;
    vec3 viewDirection = normalize(cameraPosWorld - fragmentWorldPosition);

    float attenuation = 1.0 / dot(directionToLight, directionToLight);

    directionToLight = normalize(directionToLight);

    vec3 lightColour = vp.lightColour.xyz * vp.lightColour.w * attenuation;
    vec3 ambientLigth = vp.ambientLightColour.xyz * vp.ambientLightColour.w;
    vec3 diffuseLigth = lightColour * max(dot(normalize(fragmentNormalWorld), directionToLight), 0);

    vec3 halfAngle = normalize(directionToLight + viewDirection);
    float blinnTerm = dot(normalize(fragmentNormalWorld), halfAngle);
    blinnTerm = clamp(blinnTerm, 0, 1);
    blinnTerm = pow(blinnTerm, 128.0);
    specularLight += vp.lightColour.xyz * vp.lightColour.w * blinnTerm;

    vec4 frag = vec4(diffuseLigth + ambientLigth, 1.0) * fragCol + vec4(specularLight, 1.0) * fragCol;
    outputColour = texture(samplert, uv) * frag;
}