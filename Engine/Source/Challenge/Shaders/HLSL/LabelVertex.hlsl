struct VS_IN
{
	float2 position : POSITION;
	float2 texCoord : TEXCOORD;
	float lineNum : LINE_NUM;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

cbuffer labelVertexData
{
	float4x4 gWVPMatrix;
	float4 gOriginAngle;
	float2 gPosition;
	float gScale;
	float gLineOffsets[20];
};

VS_OUT main( VS_IN vsIn )
{
	VS_OUT vsOut;

	int lineInt = int(vsIn.lineNum);
	float lineOffset = gLineOffsets[lineInt];
	vsOut.texCoord = vsIn.texCoord;

	float2 transPos = vsIn.position - gOriginAngle.xy;
	transPos.x += lineOffset;
	float sinA = gOriginAngle.z;
	float cosA = gOriginAngle.w;

	float2 finalPos;
	finalPos.x = (cosA * transPos.x) - (sinA * transPos.y);
	finalPos.y = (sinA * transPos.x) + (cosA * transPos.y);

	float2 position = gPosition + gScale * vsIn.position;
	vsOut.position = mul(gWVPMatrix, float4(position, 0.0, 1.0));

	return vsOut;
}