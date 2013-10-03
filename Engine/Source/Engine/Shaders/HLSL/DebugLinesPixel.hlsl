struct VS_OUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

float4 main(VS_OUT vOut) : SV_TARGET
{
	return vOut.color;
}