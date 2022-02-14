#version 330 core
#define MAX_DIRECTION_LIGHTS 1
#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 10
struct DirectionalLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 direction;
};
struct PointLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
	float constant;
	float linear;
	float quadratic;
};
struct SpotLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
	vec3 direction;
	float cutOff;
};
in vec4 vertexColor;
in vec2 texCoord0;
in vec3 worldPos;

uniform sampler2D diffuse;
uniform sampler2D specular;
uniform float directionalLightDataCount;
uniform float directionalLightDataCount;
uniform float directionalLightDataCount;
uniform DirectionalLight directionalLights[MAX_DIRECTION_LIGHTS];
uniform PointLight pointLights[MAX_DIRECTION_LIGHTS];
uniform SpotLight spotLights[MAX_DIRECTION_LIGHTS];

out vec4 FragColor;

vec3 CalcDirectionalLight(DirectionalLight directionalLight,vec3 normal,vec3 viewDir)
{

}
vec3 CalcPointLight(DirectionalLight directionalLight,vec3 normal,vec3 viewDir)
{
	
}
vec3 CalcSpotLight(DirectionalLight directionalLight,vec3 normal,vec3 viewDir)
{
	
}

void main()
{
	FragColor = texture(diffuse, texCoord0);
}
