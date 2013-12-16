struct GS_IN
{
	float4 position : SV_POSITION;
};

struct GS_OUT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

cbuffer data
{
	float4x4 gWVPMatrix : WORLDVIEWPROJ_MATRIX;
	float4 gWidth : WIDTH;
};

[maxvertexcount(4)]
void main(
	line GS_IN input[2] : SV_POSITION,
	inout TriangleStream< GS_OUT > output
)
{
	float dx = input[1].position.x - input[0].position.x;
	float dz = input[1].position.z - input[0].position.z;

	float4 perp = normalize(float4(-dz, 0.0, dx, 1.0));

	float halfWidth = gWidth * 0.5;

	float4 p1 = input[0].position + (perp * halfWidth);
	float4 p2 = input[0].position + (perp * -halfWidth);
	float4 p3 = input[1].position + (perp * halfWidth);
	float4 p4 = input[1].position + (perp * -halfWidth);

	GS_OUT v1;
	v1.position = mul(gWVPMatrix, p1);
	v1.texCoord = float2(0, 0);

	GS_OUT v2;
	v2.position = mul(gWVPMatrix, p2);
	v2.texCoord = float2(1, 0);

	GS_OUT v3;
	v3.position = mul(gWVPMatrix, p3);
	v3.texCoord = float2(0, 1);

	GS_OUT v4;
	v4.position = mul(gWVPMatrix, p4);
	v4.texCoord = float2(1, 1);

	output.Append(v1);
	output.Append(v2);
	output.Append(v3);

	output.Append(v1);
	output.Append(v3);
	output.Append(v4);
}