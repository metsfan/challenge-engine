Texture2D gTexture : register(t0); 
 
sampler gTriLinearSam = 
sampler_state
{
    Texture = <gTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

cbuffer color : register(b11)
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
	if(gColor.a != 0) {
		return gColor;
	}

	float4 Kd = gTexture.Sample(gTriLinearSam, vOut.texCoord);
	return Kd;
}