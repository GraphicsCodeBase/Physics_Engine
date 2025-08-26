#version 460

in vec3 fragPos;
in vec3 normal;

out vec4 out_color;

uniform vec3 lightPos;    // point light position in world space
uniform vec3 lightColor;  // color/intensity of the light
uniform vec4 objectColor; // object color

void main()
{
    vec3 N = normalize(normal);
    vec3 L = normalize(lightPos - fragPos); // point light direction

    // distance attenuation
    float lightRadius = 40.0;
    float distance = length(lightPos - fragPos);
    float attenuation = clamp(1.0 - distance / lightRadius, 0.0, 1.0);

    // ambient lighting
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse shading
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = diff * lightColor;

    // combine and apply attenuation
    vec3 result = (ambient + diffuse) * attenuation * objectColor.rgb;

    out_color = vec4(result, objectColor.a);
}
