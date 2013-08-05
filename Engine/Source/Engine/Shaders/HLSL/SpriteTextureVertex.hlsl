
 struct VS_IN
 {
	 float3 position : POSITION;
	 float2 texCoord : TEXCOORD;
 };

 struct VS_OUT
 {
	 float4 position : SV_POSITION;
	 float2 texCoord : TEXCOORD;
 };

 cbuffer cbMatrices
 {
	 float4x4 gWVPMatrix;
 };


VS_OUT main( VS_IN vIn )
{
	VS_OUT outPos;

	outPos.texCoord = vIn.texCoord;
	outPos.position = mul(gWVPMatrix, float4(vIn.position, 1.0));

	return outPos;
}