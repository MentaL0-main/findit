#version 330 core
out vec4 FragColor;

uniform vec3 uObjectColor;
in vec3 Normal;

void main() {
    FragColor = vec4(uObjectColor, 1.0);

    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * uObjectColor;

    FragColor = vec4(result, 1.0);
}
