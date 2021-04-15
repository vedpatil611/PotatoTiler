#version 330 core

in vec2 texCoords;

out vec4 colour;

uniform sampler2D uTex;
uniform bool uHasTex = false;

void main()
{
	if(uHasTex)
		colour =  texture(uTex, texCoords);
	else
		colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}