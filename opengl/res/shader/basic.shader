#SHADER VERTEX
#version 330 core

layout (location = 0) in vec3 aVertices;
void main()
{
   gl_Position = vec4(aVertices.xyz, 1.0);
}


#SHADER FRAGMENT
#version 330 core

out vec4 FragColor;
void main()
{
   FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}

