#SHADER VERTEX
#version 330 core

in layout(location = 0) vec3 aVertices;
in layout(location = 1) vec3 aNormal;

out vec3 ovFragPos;
out vec3 ovNormal;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aVertices.xyz, 1.0);
    ovFragPos = vec3(uModel * vec4(aVertices, 1.0f));
    ovNormal = mat3(transpose(inverse(model))) * aNormal;
}


#SHADER FRAGMENT
#version 330 core
in vec3 ovFragPos;
in vec3 ovNormal;

out vec4 FragColor;

uniform vec3 uLightSourcePos;

void main()
{
    vec3 lightColor = vec3(0.0, 1.0, 0.0);
    vec3 toyColor = vec3(1.0, 0.5, 0.35);
    float ambientStrength = 0.1;

    vec3 normal = normalize(ovNormal);
    vec3 lightDirection = normalize(uLightSourcePos - ovFragPos);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (diff + ambientStrength) * toyColor;

    FragColor = vec4(result, 1.0);
}



