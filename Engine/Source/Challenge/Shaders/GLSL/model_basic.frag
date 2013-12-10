#version 410

//in vec3 LightIntensity;
in vec3 Position;
in vec3 Normal;
in vec3 TexCoord;

uniform sampler2D Tex1;
uniform vec4 LightPosition; 
uniform vec3 LightIntensity; 
uniform vec3 Kd; // Diffuse reflectivity 
uniform vec3 Ka; // Ambient reflectivity 
uniform vec3 Ks; // Specular reflectivity 
uniform float Shininess; // Specular shininess factor */layout( location = 0 ) out vec4 FragColor;

layout (location = 0) out vec4 FragColor;

vec3 ads() { 
	vec3 n = normalize( Normal ); 
	vec3 s = normalize( vec3(LightPosition) - Position );
	vec3 v = normalize(vec3(-Position)); 
	vec3 r = reflect( -s, n ); 
	return LightIntensity * ( Ka + Kd * max( dot(s, n), 0.0 ) + Ks * pow( max( dot(r,v), 0.0 ), Shininess ) ); 
} 	
void main() { 
	vec4 texColor = texture(Tex1, vec2(TexCoord.x, TexCoord.y));
	//gl_FragColor = vec4(ads(), 1.0) * texColor;
	gl_FragColor = texColor;
	//gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}


/*void main() {
	vec3 lc = vec3(139, 125, 107);
	vec3 uc = vec3(238, 203, 173);
	float randR = rand(Color, lc.x, uc.x);
	float randG = rand(Color, lc.y, uc.y);
	float randB = rand(Color, lc.z, uc.z);
	vec3 randColor = vec3(randR/255.0, randG/255.0, randB/255.0);
	float heightFactor = Color.y * 0.01;
	float heightR = heightColor(heightFactor, lc.x, uc.x);
	float heightG = heightColor(heightFactor, lc.y, uc.y);
	float heightB = heightColor(heightFactor, lc.z, uc.z);
	vec3 heightColor = vec3(heightR/255.0, heightG/255.0, heightB/255.0);
	FragColor = vec4(heightColor, 1.0);
	vec3 tnorm = normalize( NormalMatrix * Normal); 
	vec4 eyeCoords = ModelViewMatrix * vec4(Position,1.0); 
	vec3 s = normalize(vec3(LightPosition - eyeCoords)); // The diffuse shading equation
	vec3 LightIntensity = Ld * Kd * max( dot( s, tnorm ), 0.0 ); // Convert position to clip coordinates and pass along gl_Position = MVP * vec4(VertexPosition,1.0);

	FragColor = vec4(LightIntensity, 1.0);
}*/