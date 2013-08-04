struct VS_OUT
{
	float4 pos : SV_POSITION;
};

cbuffer colorBuffer
{
	float4 gColor;
}

float4 main( VS_OUT psIn ) : SV_TARGET
{
	return gColor;
}