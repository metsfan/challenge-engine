Texture2D gBackgroundImage;

cbuffer cbControlData
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