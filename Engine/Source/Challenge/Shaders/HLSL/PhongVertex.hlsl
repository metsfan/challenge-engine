struct VS_IN
{
	float4 pos : POSITION;
	float3 normal : NORMAL;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float3 worldPos : POSITION;
	float3 normal : NORMAL;
	float3 color : COLOR;
};

cbuffer matrices
{
	float4x4 gWVPMatrix;
	float4x4 gWorldMatrix;
	float3x3 gNormalMatrix;
}

VS_OUT main( VS_IN vsIn )
{
	VS_OUT vsOut;

	vsOut.pos = mul(vsIn.pos, gWVPMatrix);
	vsOut.normal = normalize(mul(vsIn.normal, gNormalMatrix));
	vsOut.worldPos = mul(vsIn.pos, gWorldMatrix);

	/*if(vsIn.normal.x == 1.0 && vsIn.normal.y == 0.0 && vsIn.normal.z == 0.0) {
		vsOut.color = float3(1.0, 0.0, 0.0);
	} else if(vsIn.normal.x == -1.0 && vsIn.normal.y == 0.0 && vsIn.normal.z == 0.0) {
		vsOut.color = float3(0.0, 1.0, 0.0);
	} else if(vsIn.normal.x == 0.0 && vsIn.normal.y == 1.0 && vsIn.normal.z == 0.0) {
		vsOut.color = float3(0.0, 0.0, 1.0);
	} else if(vsIn.normal.x == 0.0 && vsIn.normal.y == -1.0 && vsIn.normal.z == 0.0) {
		vsOut.color = float3(1.0, 1.0, 0.0);
	} else if(vsIn.normal.x == 0.0 && vsIn.normal.y == 0.0 && vsIn.normal.z == 1.0) {
		vsOut.color = float3(1.0, 0.0, 1.0);
	} else if(vsIn.normal.x == 0.0 && vsIn.normal.y == 0.0 && vsIn.normal.z == -1.0) {
		vsOut.color = float3(0.0, 1.0, 1.0);
	}*/

	return vsOut;
}