Texture2D gTexture : register(t0); 
 
SamplerState gTriLinearSam : register(s0);

cbuffer color
{
	float4 gColor;
}

struct VS_OUT
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float3 worldPosition : POSITION;
	float2 texCoord : TEXCOORD;
	float3 lightDir : LIGHT_DIRECTION;
};

const float4 lineColor = (0, 0, 0, 1);

float4 main(VS_OUT vOut) : SV_TARGET
{             
	float4 Kd = gTexture.Sample(gTriLinearSam, vOut.texCoord);
	return Kd;
}