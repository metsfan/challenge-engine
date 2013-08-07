 struct VS_OUT
 {
	 float4 position : SV_POSITION;
	 float2 texCoord : TEXCOORD;
 };

cbuffer colorBuffer : register(b5)
{
	float4 gColor;
}

float4 main( VS_OUT psIn ) : SV_TARGET
{
	return gColor;
}