Texture2D gFontTexture : register(t0);

SamplerState gTriLinearSam : register(s0);

 struct VS_OUT
 {
	 float4 position : SV_POSITION;
	 float2 texCoord : TEXCOORD;
 };

float4 main(VS_OUT vOut) : SV_TARGET
{
	float4 color = gFontTexture.Sample(gTriLinearSam, vOut.texCoord);

	return color;
}