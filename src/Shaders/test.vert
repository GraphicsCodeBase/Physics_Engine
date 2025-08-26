#version 460

layout(location = 0) in vec3 attr_position;

layout(std430, binding = 0) buffer InstanceData
{
    mat4 models[];
};

uniform mat4 uniform_vp;

void main()
{
    mat4 model = models[gl_InstanceID];
    gl_Position = uniform_vp * model * vec4(attr_position, 1.0);
}
