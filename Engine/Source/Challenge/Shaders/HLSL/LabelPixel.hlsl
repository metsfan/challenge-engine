Texture2D gAtlasTexture;

sampler gTriLinearSam =
sampler_state
{
	Texture = <gAtlasTexture>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

struct PS_IN
{
	float4 position: SV_POSITION;
	float2 texCoord : TEXCOORD;
};

cbuffer labelPixelData
{
	float gAlpha;
	float4 gColor;
};

float4 main(PS_IN psIn) : SV_TARGET
{
	float alpha = gAtlasTexture.Sample(gTriLinearSam, psIn.texCoord).a;
	return gColor * alpha * gAlpha;
}