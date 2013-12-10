Texture2D gBackgroundImage : register(t1);

cbuffer cbControlData : register(b6)
{
	float4 gColor;
};
 
sampler gTriLinearSam = 
sampler_state
{
    Texture = <gBackgroundImage>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

 struct VS_OUT
 {
	 float4 position : SV_POSITION;
	 float2 texCoord : TEXCOORD;
 };

float4 main(VS_OUT vOut) : SV_TARGET
{             
	return gBackgroundImage.Sample(gTriLinearSam, vOut.texCoord);
}