#SHADER VERTEX
#version 330 core

in layout (location = 0) vec3 aVertices;
in layout (location = 1) vec2 aTexCoord;

out vec2 oTexCoord;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
   gl_Position =  uProjection * uView * uModel * vec4(aVertices.xyz, 1.0);
   oTexCoord = aTexCoord;
}


#SHADER FRAGMENT
#version 330 core

out vec4 FragColor;
in vec2 oTexCoord;

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;

void main()
{
   FragColor = mix(texture(ourTexture0, oTexCoord), texture(ourTexture1, vec2(oTexCoord.x, oTexCoord.y)), 0.2);
}

