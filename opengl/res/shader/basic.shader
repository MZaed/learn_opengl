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
uniform vec4 u_color;

void main()
{
   FragColor = u_color;
}

