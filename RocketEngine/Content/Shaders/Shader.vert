#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout(location = 1) out vec3 fragPosition;
layout(location = 2) out vec3 fragNormal;

uniform mat4 viewProj;
uniform mat4 model;

void main() 
{
    gl_Position = viewProj * model * vec4(position, 1.0);

    fragPosition = vec3(model * vec4(position, 1.0));
    fragNormal = mat3(transpose(inverse(model))) * normal; 
}
