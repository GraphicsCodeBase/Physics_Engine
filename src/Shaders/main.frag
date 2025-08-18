#version 330

in vec3 fragPos;
in vec3 normal;

out vec4 out_color;

uniform vec3 lightDir;     // direction of the light in world space
uniform vec3 lightColor;   // color light intensity
uniform vec4 objectColor;  // color of the object (now with alpha)

void main()
{
    vec3 N = normalize(normal);
    vec3 L = normalize(-lightDir); // directional light points opposite direction

    // diffuse shading 
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = diff * lightColor;

    // apply object color.rgb, keep alpha
    vec3 color = diffuse * objectColor.rgb;
    out_color = vec4(color, objectColor.a);
}