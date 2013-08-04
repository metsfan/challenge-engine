TextureCube gSkyboxTexture : register(t1);

SamplerState gTriLinearSam : register(s0);

struct PS_IN
{
	float4 position : SV_POSITION;
	float3 texCoord : TEXCOORD;
};

float4 main(PS_IN psIn) : SV_TARGET
{
	float4 color = gSkyboxTexture.Sample(gTriLinearSam, psIn.texCoord);

	return color;
}