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
	float strength;
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
	float strength;
};
struct SpotLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
	vec3 direction;
	float cutOff;
	float outCutOff;
	float strength;
};
vec3 CalcDirectionalLight(DirectionalLight light,vec3 normal,vec3 viewDir);
vec3 CalcPointLight(PointLight light,vec3 normal,vec3 viewDir);
vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 viewDir);

in vec4 vertexColor;
in vec2 texCoord[8];
in vec3 fragPos;
in vec3 normal;

uniform vec3 viewDir;
uniform sampler2D diffuse[8];
uniform sampler2D specular[8];


uniform float shininess;
uniform int directionalLightDataCount;
uniform int pointLightDataCount;
uniform int spotLightDataCount;
uniform DirectionalLight directionalLights[MAX_DIRECTION_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

out vec4 FragColor;



void main()
{
	vec3 output;
	for(int i = 0;i<min(MAX_DIRECTION_LIGHTS,directionalLightDataCount);i++)
	{
		output += CalcDirectionalLight(directionalLights[i],normal,viewDir);
	}
	for(int i = 0;i<min(MAX_POINT_LIGHTS,pointLightDataCount);i++)
	{
		output += CalcPointLight(pointLights[i],normal,viewDir);
	}
	for(int i = 0;i<min(MAX_SPOT_LIGHTS,spotLightDataCount);i++)
	{
		output += CalcSpotLight(spotLights[i],normal,viewDir);
	}
	FragColor = vec4(output,1.0);
}
vec3 CalcDirectionalLight(DirectionalLight light,vec3 normal,vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal,lightDir), 0.0);
	vec3 reflectDir = reflect(normalize(-lightDir), normalize(normal));
	float spec = pow(min(max(dot(normalize(-viewDir), normalize(reflectDir)), 0.0),1.0), shininess);
	vec3 ambient  = light.ambient  * vec3(texture(diffuse[0], texCoord[0]));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(diffuse[0], texCoord[0])) * light.strength;
    vec3 specular = light.specular + spec *  vec3(texture(specular[0], texCoord[0])) * light.strength;
	return (ambient + diffuse + specular) * light.strength;
}
vec3 CalcPointLight(PointLight light,vec3 normal,vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(normalize(-lightDir), normalize(normal));
	float spec = pow(min(max(dot(normalize(-viewDir), normalize(reflectDir)), 0.0),1.0), shininess);
	float distance = length(light.position - fragPos);
	float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * distance * distance);
	vec3 ambient  = light.ambient  * vec3(texture(diffuse[0], texCoord[0]));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(diffuse[0], texCoord[0]));
    vec3 specular = light.specular * spec * vec3(texture(specular[0], texCoord[0]));
	ambient *= attenuation;
	diffuse *= attenuation  * light.strength;
	specular *= attenuation  * light.strength;
	return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float theta = dot(normalize(light.direction), -lightDir);
	float epsilon = light.cutOff - light.outCutOff;
	float intensity = clamp((theta - light.outCutOff)/epsilon,0,1);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(normalize(-lightDir), normalize(normal));
	float spec = pow(min(max(dot(normalize(-viewDir), normalize(reflectDir)), 0.0),1.0), shininess);
	vec3 ambient  = light.ambient  * vec3(texture(diffuse[0], texCoord[0]));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(diffuse[0], texCoord[0]));
    vec3 specular = light.specular * spec * vec3(texture(specular[0], texCoord[0]));
	ambient *= intensity;
	diffuse *= intensity * light.strength;
	specular *= intensity * light.strength;
	return (ambient + diffuse + specular);
}