#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

uniform mat4 uModel = mat4(1.0f);
uniform mat4 uView = mat4(1.0f);
uniform mat4 uProj = mat4(1.0f);

out vec2 texCoords;

void main()
{
	gl_Position = uProj * uView * uModel * vec4(position, 0.0f, 1.0f);
	texCoords = uv;
}
