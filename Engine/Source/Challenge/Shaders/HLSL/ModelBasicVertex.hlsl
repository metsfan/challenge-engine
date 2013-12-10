struct VS_IN
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float3 worldPosition : POSITION;
	float2 texCoord : TEXCOORD;
	float3 lightDir : LIGHT_DIRECTION;
};

cbuffer matrices : register(b5)
{
	float4x4 gWVPMatrix;
	float4x4 gWorldMatrix;
	float3x3 gNormalMatrix;
};

VS_OUT main( VS_IN vIn)
{
	VS_OUT vOut;

	float4 position = float4(vIn.position, 1.0);

	vOut.position = mul(gWVPMatrix, position); 
	vOut.normal = mul((float3x3)gWorldMatrix, vIn.normal);
	vOut.worldPosition = mul(gWorldMatrix, position);
	vOut.texCoord = float2(vIn.texCoord.x, 1.0 - vIn.texCoord.y);

	float3 lightDir = normalize(float3(0, 0, 1));
	vOut.lightDir = mul((float3x3)gWorldMatrix, lightDir);

	return vOut;
};