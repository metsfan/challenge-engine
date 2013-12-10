
struct VS_IN
{
	float3 position : POSITION;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
	float3 texCoord : TEXCOORD;
};

cbuffer matrices : register(b2)
{
	float4x4 gWVPMatrix;
};

VS_OUT main(VS_IN vsIn)
{
	VS_OUT vsOut;

	vsOut.position = mul(gWVPMatrix, float4(vsIn.position, 1.0));
	//vsOut.texCoord = float3(vsIn.texCoord, vsIn.faceId);
	vsOut.texCoord = vsIn.position;

	return vsOut;
}