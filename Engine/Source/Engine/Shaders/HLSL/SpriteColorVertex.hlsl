
struct VS_IN
{
	float3 pos : POSITION;
	float2 texCoord : TEXCOORD;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

cbuffer matrices
{
	float4x4 gWVPMatrix;
};

VS_OUT main( VS_IN vsIn )
{
	VS_OUT vsOut;

	vsOut.pos = mul(float4(vsIn.pos, 1.0), gWVPMatrix);
	vsOut.texCoord = vsIn.texCoord;

	return vsOut;
}