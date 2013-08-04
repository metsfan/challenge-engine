struct VS_IN
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
	float4 boneWeights: BONE_WEIGHTS;
	float4 boneIndices : BONE_INDICES;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float3 worldPosition : POSITION;
	float2 texCoord : TEXCOORD;
	float3 lightDir : LIGHT_DIRECTION;
};

cbuffer matrices : register(b1)
{
	float4x4 gWVPMatrix;
	float4x4 gWorldMatrix;
	float3x3 gNormalMatrix;
};

#define MAX_BONES 64

cbuffer bones : register(b2)
{
	float4x4 gBoneMatrices[MAX_BONES];
};

VS_OUT main( VS_IN vsIn)
{
	VS_OUT vOut;

	float3 position = float3(0.0, 0.0, 0.0);
	float3 normal = float3(0.0, 0.0, 0.0);
	float4 startPosition = float4(vsIn.position, 1.0);
	float4 startNormal = float4(vsIn.normal, 0.0);

	int boneIndex;

	boneIndex = int(vsIn.boneIndices[0]);
	position += vsIn.boneWeights[0] * mul(startPosition, gBoneMatrices[boneIndex]);
	normal += vsIn.boneWeights[0] * mul(startNormal, gBoneMatrices[boneIndex]);

	boneIndex = int(vsIn.boneIndices[1]);
	position += vsIn.boneWeights[1] * mul(startPosition, gBoneMatrices[boneIndex]);
	normal += vsIn.boneWeights[1] * mul(startNormal, gBoneMatrices[boneIndex]);

	boneIndex = int(vsIn.boneIndices[2]);
	position += vsIn.boneWeights[2] * mul(startPosition, gBoneMatrices[boneIndex]);
	normal += vsIn.boneWeights[2] * mul(startNormal, gBoneMatrices[boneIndex]);

	boneIndex = int(vsIn.boneIndices[3]);
	position += vsIn.boneWeights[3] * mul(startPosition, gBoneMatrices[boneIndex]);
	normal += vsIn.boneWeights[3] * mul(startNormal, gBoneMatrices[boneIndex]);

	float4 finalPosition = float4(position, 1.0);
	float4 finalNormal = float4(normal, 0.0);

	vOut.position = mul(gWVPMatrix, finalPosition); 
	vOut.normal = normalize(mul((float3x3)gWorldMatrix, normal));
	vOut.worldPosition = mul(gWorldMatrix, finalPosition);
	vOut.texCoord = vsIn.texCoord;

	float3 lightDir = normalize(float3(0, 0, 1));
	vOut.lightDir = normalize(mul((float3x3)gWorldMatrix, lightDir));


	return vOut;
};