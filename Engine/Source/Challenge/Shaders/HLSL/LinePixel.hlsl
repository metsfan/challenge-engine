struct PS_IN
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

cbuffer color
{
	float4 gColor : COLOR;
};

float4 main(PS_IN psIn) : SV_TARGET
{
	return gColor;
}