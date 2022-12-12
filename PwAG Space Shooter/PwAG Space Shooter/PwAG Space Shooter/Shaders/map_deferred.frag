#version 430 

uniform sampler2D gBuffer_Position;
uniform sampler2D gBuffer_Normal;
uniform sampler2D gBuffer_AlbedoSpec;

uniform vec3 cameraPos;

in vec2 v_TextCoord;

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

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 fragColor, float Specular);

void main()
{
	if (gl_FrontFacing) {

		vec3 FragPos = texture(gBuffer_Position, v_TextCoord).rgb;
		vec3 Normal = texture(gBuffer_Normal, v_TextCoord).rgb;
		vec3 Albedo = texture(gBuffer_AlbedoSpec, v_TextCoord).rgb * 0.1;
		float Specular = texture(gBuffer_AlbedoSpec, v_TextCoord).a;
		
		vec3 viewDir = normalize(cameraPos - FragPos);

		vec3 result = vec3(0, 0, 0);
		for(int i = 0; i < pointLightsCount; ++i)
		{
			result += calculatePointLight(pointLights[i], Normal, FragPos, viewDir, Albedo, Specular);
		}

		gl_FragColor = vec4(result, 1.0);
	}
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 fragColor, float Specular)
{
	vec3 posToLightDirectionVectorDiffuse = normalize(light.position - fragPos);
	vec3 posToLightDirectionVectorSpecular = normalize(light.position - fragPos);

	// diffuse light
	float diffuseLight = max(dot(normal, posToLightDirectionVectorDiffuse), 0.0);

	// specular light
	vec3 reflectDirVec = reflect(-posToLightDirectionVectorSpecular, normal);
	float specularConstant = pow(max(dot(viewDir, reflectDirVec), 0.0), 35);
	//vec3 halfwayDir = normalize(posToLightDirectionVector + viewDir);
	//float specularConstant = pow(max(dot(normal, halfwayDir), 0.0), 205);

	// attentuation
	float distance = length(light.position - fragPos);
	float attentuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	vec3 ambientFinal = light.ambient * fragColor;
	vec3 diffuseFinal = light.diffuse * diffuseLight * fragColor;
	vec3 specularFinal = light.specular * specularConstant * Specular;

	ambientFinal *= attentuation;
	diffuseFinal *= attentuation;
	specularFinal *= attentuation;

	return ambientFinal + diffuseFinal + specularFinal;
}