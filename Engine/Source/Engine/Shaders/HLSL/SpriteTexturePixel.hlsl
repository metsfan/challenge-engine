Texture2D gBackgroundImage : register(t0);

cbuffer cbControlData : register(b6)
{
	float4 gColor;
};
 
SamplerState gTriLinearSam : register(s0);

 struct VS_OUT
 {
	 float4 position : SV_POSITION;
	 float2 texCoord : TEXCOORD;
 };

float4 main(VS_OUT vOut) : SV_TARGET
{             
	return gBackgroundImage.Sample(gTriLinearSam, vOut.texCoord) * gColor;
}