struct VS_IN
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

cbuffer matrices
{
	float4x4 gWVPMatrix;
};

VS_OUT main( VS_IN vIn )
{
	VS_OUT vOut;

	vOut.position = mul(gWVPMatrix, float4(vIn.position, 1.0));
	vOut.color = vIn.color;

	return vOut;
}