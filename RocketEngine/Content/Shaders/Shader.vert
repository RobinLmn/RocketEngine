#version 450

layout(binding = 0) uniform UniformBuffer 
{
    mat4 model;
    mat4 view;
    mat4 proj;
} uniform;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

layout(location = 0) out vec3 fragColor;

void main() 
{
    gl_Position = uniform.proj * uniform.view * uniform.model * vec4(position, 1.0);
    fragColor = color;
}
