#SHADER VERTEX
#version 330 core

layout (location = 0) in vec3 aVertices;
layout (location = 1) in vec3 aColor;
out vec3 oColor;
void main()
{
   gl_Position = vec4(aVertices.xyz, 1.0);
   oColor = aColor;
}


#SHADER FRAGMENT
#version 330 core

out vec4 FragColor;
in vec3 oColor;

void main()
{
   FragColor = vec4(oColor, 1.0);
}

