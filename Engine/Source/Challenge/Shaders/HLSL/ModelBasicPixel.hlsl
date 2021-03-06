Texture2D gTexture; 
 
sampler gTriLinearSam = 
sampler_state
{
    Texture = <gTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

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
	/*if(gColor.a != 0) {
		return gColor;
	}*/

	float4 texColor = gTexture.Sample(gTriLinearSam, vOut.texCoord);
	float4 Kd = 1 - ((1 - texColor) * (1 - gColor));
	return texColor;
}