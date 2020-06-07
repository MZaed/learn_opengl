#SHADER VERTEX
#version 330 core

layout (location = 0) in vec3 aVertices;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec3 oColor;
out vec2 oTexCoord;
void main()
{
   gl_Position = vec4(aVertices.xyz, 1.0);
   oColor = aColor;
   oTexCoord = aTexCoord;
}


#SHADER FRAGMENT
#version 330 core

out vec4 FragColor;
in vec3 oColor;
in vec2 oTexCoord;

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;

void main()
{
   FragColor = mix(texture(ourTexture0, oTexCoord), texture(ourTexture1, vec2(oTexCoord.x, oTexCoord.y)), 0.2);
}

