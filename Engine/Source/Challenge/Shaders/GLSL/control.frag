#version 410

in vec3 Position;
in vec2 TexCoord;

uniform vec4 BackgroundColor;
uniform vec4 Color;
uniform int HasText;
uniform int HasTexture;
uniform sampler2D BackgroundImage;
uniform sampler2D FontTexture;

void main()
{
	vec4 finalColor;
	if(HasText > 0) {
		finalColor = texture2D(FontTexture, TexCoord) + vec4(Color.xyz, 0.0);
	} else if(HasTexture > 0) {
		finalColor = texture2D(BackgroundImage, TexCoord);
	} else {
		finalColor = BackgroundColor;
	}
	
	gl_FragColor = finalColor;
}