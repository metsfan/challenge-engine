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
	float2 gridPosition: GRID_POSITION;
};

const float4 lineColor = (0, 0, 0, 1);

float4 main(VS_OUT vOut) : SV_TARGET
{             
	//float4 Kd = gTexture.Sample(gTriLinearSam, vOut.texCoord);
	//return Kd;
	//return float4(1.0, 0.0, 0.0, 1.0);

	float4 color = float4(1.0, 0.0, 0.0, 1.0);

	color = lerp(lineColor, color, step(max(frac(vOut.gridPosition.x), frac(vOut.gridPosition.y)), 0.9));

	return color;
}