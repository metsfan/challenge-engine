#version 410

layout (location = 2) in vec3 VertexPosition;
layout (location = 3) in vec3 VertexNormal;
layout (location = 4) in vec2 VertexTexCoord;
//out vec3 LightIntensity;
out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 ModelViewMatrix; 
uniform mat3 NormalMatrix; 
uniform mat4 ProjectionMatrix; 
uniform mat4 MVP; 

//out vec3 Color;

void main() {
	/*vec3 tnorm = normalize( NormalMatrix * VertexNormal); 
	vec4 eyeCoords = ModelViewMatrix * vec4(VertexPosition,1.0); 
	vec3 s = normalize(vec3(LightPosition - eyeCoords)); // The diffuse shading equation
	LightIntensity = Ld * Kd * max( dot( s, tnorm ), 0.0 ); // Convert position to clip coordinates and pass along gl_Position = MVP * vec4(VertexPosition,1.0);*/
	TexCoord = VertexTexCoord;
	Normal = normalize( NormalMatrix * VertexNormal); 
	Position = vec3( ModelViewMatrix * vec4(VertexPosition,1.0) ); 
	gl_Position = MVP * vec4(VertexPosition,1.0);
	//Position = VertexPosition;
	//Normal = VertexNormal;
	//Color = VertexPosition;
	//gl_Position = MVP * vec4(VertexPosition,1.0);
}
