#version 330

in vec3 fragPos;
in vec3 normal;

out vec4 out_color;

uniform vec3 lightDir;     // direction of the light in world space
uniform vec3 lightColor;   // color light intensity
uniform vec4 objectColor;  // color of the object (with alpha)

void main()
{
    vec3 N = normalize(normal);
    vec3 L = normalize(-lightDir); // directional light points opposite direction

    // ambient lighting
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse shading 
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = diff * lightColor;

    // final color
    vec3 result = (ambient + diffuse) * objectColor.rgb;
    out_color = vec4(result, objectColor.a);
}
