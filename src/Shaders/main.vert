#version 130

in vec3 attr_position;

uniform mat4 uniform_vp;
uniform mat4 uniform_m2w;

void main()
{
    vec4 vertex = vec4(attr_position, 1.0f);
    gl_Position = uniform_vp * uniform_m2w * vertex;
}
