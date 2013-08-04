#define MAX_LIGHTS 1

struct VS_OUT
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float3 worldPosition : POSITION;
	float2 texCoord : TEXCOORD;
	float3 lightDir : LIGHT_DIRECTION;
};

struct SHADING_PARAMS
{
	float3 diffuse;
	float3 specular;
	float3 ambient;
	float shininess;
};

struct LIGHT_SOURCE
{
	float intensity; 
	float3 direction;
	float3 position;
};
 
cbuffer lightParams
{
	LIGHT_SOURCE lightSources[MAX_LIGHTS];
	SHADING_PARAMS shadingParams;
	int numLights;
};

float4 main(VS_OUT psIn) : SV_TARGET
{
	/*float4 Kd = gTexture.Sample(gTriLinearSam, vOut.texCoord);
	float3 Ka = float3(0.2, 0.2, 0.2) / 3.14159f;
	float m = 1.0;
	float3 Ks = ((m + 8) / (8 * 3.14159f)) * float3(1.0, 1.0, 1.0);
	//float3 Ka = float3(0.1, 0.1, 0.1);
	//float3 Ks = float3(0.1, 0.1, 0.1);

	float3 surfacePosition = vOut.worldPosition;
	float3 viewPosition = float3(0.0, 0.0, 0.0);
	float3 v = normalize(viewPosition - surfacePosition);
	float3 Lo = float3(0.0, 0.0, 0.0);
	
	//Kd = float3(1.0, 0.0, 0.0);
	
	//Ks = float3(0.0, 0.0, 1.0);
	float3 EL = float3(10.0, 10.0, 10.0);
	//float3 n = normalize(float3(-0.5, -0.5, 1));
	float3 n = normalize(vOut.normal);
	float3 d = normalize(vOut.lightDir);
	float3 h = normalize(v + d);
	float cosTh = saturate(dot(n, h));
	float cosTi = saturate(dot(n, d));
	Lo += (Ka + Ks * pow(cosTh, m)) * Kd * cosTi * 3;

	return float4(Lo, 1.0);

	/*float3 n = normalize(vOut.normal);
	float3 s = normalize(float3(0,0,0) - vOut.worldPosition);
	float3 v = normalize(-vOut.worldPosition);
	float3 r = reflect(-s, n);

	float3 color = Ka + Kd * max(dot(s, n), 0.0) + Ks * pow(max(dot(r, v), 0.0), m);*/
	
	//return Kd;*/

	return float4(1.0, 0.0, 0.0, 1.0);
	//return float4(vOut.texCoord, 0.0, 1.0);
	//return float4(n, 1.0);
	//return color;
}