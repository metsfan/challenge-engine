struct PS_IN
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD0;
};

cbuffer color
{
	float4 gColor : COLOR;
};

float4 main(PS_IN psIn) : SV_TARGET
{
	float dist = distance(psIn.texCoord, float2(0.5, 0.5));
	if (dist < 0.5) {
		return gColor;
	}
	
	return float4(0, 0, 0, 0);
}