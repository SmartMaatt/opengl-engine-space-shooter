#version 430 

layout (location = 0) out vec4 frag;

uniform sampler2D diffuse;
uniform sampler2D specular;
uniform sampler2D normalMap;

uniform vec3 cameraPos;

in vec3 v_Color;
in vec2 v_TextCoord;
in vec3 v_Normal;
in vec3 v_Position;

in vec3 v_Offset;

in mat3 TBN;

struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define MAX_POINT_LIGHT_COUNT 64

uniform PointLight pointLights[MAX_POINT_LIGHT_COUNT];
uniform int pointLightsCount;

float lightBrightness = 2;
float lightPower = 2;

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	if (gl_FrontFacing) {
		
		vec3 norm = normalize(v_Normal);
		vec3 viewDir = normalize(cameraPos - v_Position) * TBN;

		vec3 result = vec3(0, 0, 0);
		for(int i = 0; i < pointLightsCount; ++i)
		{
			result += calculatePointLight(pointLights[i], norm, v_Position, viewDir);
		}

		frag = vec4(result, 1.0);
	}
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 posToLightDirectionVectorDiffuse = normalize(light.position + v_Offset - fragPos);
	vec3 posToLightDirectionVectorSpecular = normalize(light.position - fragPos);

	// diffuse light
	normal = normal + texture(normalMap, v_TextCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	float diffuseLight = max(dot(normal, posToLightDirectionVectorDiffuse), 0.0);

	// specular light
	vec3 reflectDirVec = reflect(-posToLightDirectionVectorSpecular, normal);
	float specularConstant = pow(max(dot(viewDir, reflectDirVec), 0.0), 35);
	//vec3 halfwayDir = normalize(posToLightDirectionVector + viewDir);
	//float specularConstant = pow(max(dot(normal, halfwayDir), 0.0), 205);

	// attentuation
	float distance = length(light.position - v_Position) / lightBrightness;
	float attentuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	vec3 diffuseTextured = texture(diffuse, v_TextCoord).rgb;
	vec3 specularTextured = texture(specular, v_TextCoord).rgb;
	
	vec3 ambientFinal = light.ambient * diffuseTextured;
	vec3 diffuseFinal = light.diffuse * diffuseLight * diffuseTextured;
	vec3 specularFinal = light.specular * specularConstant * specularTextured;

	ambientFinal *= attentuation;
	diffuseFinal *= attentuation;
	specularFinal *= attentuation;

	return ambientFinal + diffuseFinal * lightPower + specularFinal;
}