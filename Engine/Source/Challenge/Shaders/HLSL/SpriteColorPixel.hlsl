 struct VS_OUT
 {
	 float4 position : SV_POSITION;
	 float2 texCoord : TEXCOORD;
	 float4 frame : POSITION0;
	 float borderWidth : POSITION1;
 };

cbuffer colorBuffer
{
	float4 gColor;
	float4 gBorderColor;
}

float4 main( VS_OUT psIn ) : SV_TARGET
{
	float minX = psIn.borderWidth / psIn.frame.z;
	float minY = psIn.borderWidth / psIn.frame.w;
	float maxX = 1.0 - minX;
	float maxY = 1.0 - minY;

	if (psIn.texCoord.x < minX || psIn.texCoord.x > maxX ||
	psIn.texCoord.y < minY || psIn.texCoord.y > maxY) {
		return gBorderColor;
	}

	return gColor;
}