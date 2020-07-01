#SHADER VERTEX
#version 330 core

in layout (location = 0) vec3 aVertices;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
   gl_Position =  uProjection * uView * uModel * vec4(aVertices.xyz, 1.0);
}


#SHADER FRAGMENT
#version 330 core

out vec4 FragColor;

uniform vec4 uColor;

void main()
{
	FragColor = uColor;
}

