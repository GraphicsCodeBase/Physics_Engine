#version 460

in vec3 attr_position;
in vec3 attr_normal; // per-vertex normal.

uniform mat4 uniform_vp;

// SSBO: unlimited instance transforms
layout(std430, binding = 0) buffer InstanceData {
    mat4 models[];
};

out vec3 fragPos; // world position for lighting
out vec3 normal;  // normal in world space.

void main()
{
    mat4 model = models[gl_InstanceID];

    vec4 vertex = vec4(attr_position, 1.0f);
    vec4 worldPos = model * vertex;
    fragPos = worldPos.xyz;

    //transform normal to world space.
    normal = normalize(mat3(model) * attr_normal);

    gl_Position = uniform_vp * worldPos;
}
