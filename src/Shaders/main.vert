#version 330

in vec3 attr_position;
in vec3 attr_normal; // per-vertex normal.

uniform mat4 uniform_vp;
uniform mat4 uniform_m2w;

out vec3 fragPos; // world position for lighting
out vec3 normal;  // normal in world space.

void main()
{
    vec4 vertex = vec4(attr_position, 1.0f);
    vec4 worldPos = uniform_m2w * vertex;
    fragPos = worldPos.xyz;

    //transform normal to world space.
    normal = normalize(mat3(uniform_m2w) * attr_normal);

    gl_Position = uniform_vp * uniform_m2w * vertex;
}
