struct VS_IN
{
	float3 position : POSITION;
	float2 texCoord : TEXCOORD;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float3 worldPosition : POSITION;
	float2 texCoord : TEXCOORD;
	float3 lightDir : LIGHT_DIRECTION;
	float2 gridPosition: GRID_POSITION;
};

Texture2D gHeightMapTexture;

cbuffer heightmapData : register(b0)
{
	float4x4 gWVPMatrix;
	float2 gSize;
};

VS_OUT main( VS_IN vsIn )
{
	VS_OUT vsOut;

	float u = vsIn.position.x / gSize.x;
	float v = vsIn.position.z / gSize.y;

	float2 uv = float2(vsIn.position.x, vsIn.position.z);
	float height = gHeightMapTexture[uv];
	float4 position = float4(vsIn.position, 1.0);
	position.y = height;

	vsOut.position = mul(gWVPMatrix, position);
	vsOut.texCoord = vsIn.texCoord;
	vsOut.gridPosition = float2(vsIn.position.x, vsIn.position.z);

	return vsOut;
}