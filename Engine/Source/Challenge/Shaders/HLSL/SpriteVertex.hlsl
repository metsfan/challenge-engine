
 struct VS_IN
 {
	 float2 position : POSITION;
 };

 struct VS_OUT
 {
	 float4 position : SV_POSITION;
	 float2 texCoord : TEXCOORD;
	 float4 frame : POSITION0;
	 float borderWidth : POSITION1;
 };

 cbuffer spriteData : register(b1)
 {
	 float4x4 gWVPMatrix;
	 float4 gFrame;
	 float4 gTexFrame;
	 float gBorderWidth;
 };


VS_OUT main( VS_IN vIn )
{
	VS_OUT vsOut;

	float2 position = (gFrame.xy - gBorderWidth) + (vIn.position * (gFrame.zw + (gBorderWidth * 2)));

	vsOut.position = mul(gWVPMatrix, float4(position, 0.0, 1.0));
	vsOut.texCoord = gTexFrame.xy + (vIn.position * gTexFrame.zw);
	vsOut.frame = gFrame;
	vsOut.borderWidth = gBorderWidth;

	return vsOut;
}