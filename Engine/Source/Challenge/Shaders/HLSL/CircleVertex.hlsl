struct VS_IN
{
	float3 position : POSITION;
	float2 texCoord : TEXCOORD;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD0;
};

cbuffer matrices
{
	float4x4 gWVPMatrix : WORLDVIEWPROJ_MATRIX;
};

VS_OUT main(VS_IN vsIn)
{
	VS_OUT vsOut;

	vsOut.position = mul(gWVPMatrix, float4(vsIn.position, 1.0));
	vsOut.texCoord = vsIn.texCoord;

	return vsOut;
}