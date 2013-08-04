#version 410

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexTexCoord; 

out vec3 Position;
out vec2 TexCoord;

uniform mat4 ModelViewProjectionMatrix;

void main() 
{
	Position = VertexPosition;
	TexCoord = VertexTexCoord;
	gl_Position = ModelViewProjectionMatrix * vec4(VertexPosition, 1.0);		
}
