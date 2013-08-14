
 struct VS_IN
 {
	 float2 position : POSITION;
 };

 struct VS_OUT
 {
	 float4 position : SV_POSITION;
	 float2 texCoord : TEXCOORD;
 };

 cbuffer spriteData : register(b1)
 {
	 float4x4 gWVPMatrix;
	 float4 gFrame;
	 float4 gTexFrame;
 };


VS_OUT main( VS_IN vIn )
{
	VS_OUT vsOut;

	float2 position = gFrame.xy + (vIn.position * gFrame.zw);

	vsOut.position = mul(gWVPMatrix, float4(position, 0.0, 1.0));
	vsOut.texCoord = gTexFrame.xy + (vIn.position * gTexFrame.zw);

	return vsOut;
}