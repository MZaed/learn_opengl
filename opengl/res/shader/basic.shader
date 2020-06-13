#SHADER VERTEX
#version 330 core

in layout (location = 0) vec3 aVertices;
in layout (location = 1) vec3 aColor;
in layout (location = 2) vec2 aTexCoord;

out vec3 oColor;
out vec2 oTexCoord;

uniform mat4 uTransform;

void main()
{
   gl_Position = uTransform * vec4(aVertices.xyz, 1.0);
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

