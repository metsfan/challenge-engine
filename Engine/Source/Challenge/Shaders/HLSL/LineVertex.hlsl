struct VS_IN
{
	float3 position : POSITION;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
};

VS_OUT main(VS_IN vsIn)
{
	VS_OUT vsOut;

	vsOut.position = float4(vsIn.position, 1.0);

	return vsOut;
}