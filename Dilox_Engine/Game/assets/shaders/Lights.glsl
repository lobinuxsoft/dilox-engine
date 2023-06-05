// Basic Texture Shader
#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Normal;
layout(location = 4) in float a_TexIndex;
layout(location = 5) in float a_TilingFactor;


uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec4 v_Color;
out vec3 FragPos;
out vec3 v_Normal;

out vec2 v_TexCoord;
out flat float v_TexIndex;
out float v_TilingFactor;

void main()
{
	FragPos = vec3(u_Model * vec4(a_Position, 1.0f)); 

	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_Normal = a_Normal;
	v_TexIndex = a_TexIndex;
	v_TilingFactor = a_TilingFactor;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normal;
in flat float v_TexIndex;
in float v_TilingFactor;

in vec3 FragPos;

uniform sampler2D u_Textures[32];

uniform vec3 u_LightPosition; // Position of the light in world coordinates
uniform vec4 u_LightColor; // Color of the light
uniform float u_LightIntensity; // Intensity of the light

		struct Material 
		{				
		vec3 ambient;					
		vec3 diffuse;					
		vec3 specular;					
		float shininess;				
		};								
		
		struct DirectionalLight 
		{
		    vec3 direction;
			vec3 color;
		    vec3 ambient;
		    vec3 diffuse;
		    vec3 specular;
		};							
		
		struct PointLight 
		{
		    vec3 position;
			vec3 color;
		    vec3 ambient;
		    vec3 diffuse;
		    vec3 specular;
		    float constant;
		    float linear;
		    float quadratic;
		};

		struct SpotLight 
		{
		    vec3 position;
		    vec3 direction;
			vec3 color;
		    vec3 ambient;
		    vec3 diffuse;
		    vec3 specular;
		    float constant;
		    float linear;
		    float quadratic;
		    float cutoff;
		    float outerCutoff;
		};

		const int MAX_DIRECTIONAL_LIGHTS = 10;
		const int MAX_POINT_LIGHTS = 10;
		const int MAX_SPOT_LIGHTS = 1;

		uniform Material material;     
				uniform vec3 viewPos;           

		
		uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
		uniform PointLight pointLights[MAX_POINT_LIGHTS];
		uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

		uniform int numDirectionalLights;
		uniform int numPointLights;
		uniform int numSpotLights;

		vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) 
		{
		    vec3 lightDir = normalize(-light.direction);
		    vec3 reflectDir = reflect(-lightDir, normal);
		
		    vec3 ambient = light.ambient * material.ambient;
		    vec3 diffuse = light.diffuse * max(dot(normal, lightDir), 0.0) * material.diffuse;
		    vec3 specular = light.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * material.specular;
		
		    return (ambient + diffuse + specular) * light.color;
		}

		vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) 
		{
		    vec3 lightDir = normalize(light.position - fragPos);
		    vec3 reflectDir = reflect(-lightDir, normal);
		
		    float distance = length(light.position - fragPos);
		    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
		
		    vec3 ambient = light.ambient * material.ambient;
		    vec3 diffuse = light.diffuse * max(dot(normal, lightDir), 0.0) * material.diffuse;
		    vec3 specular = light.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * material.specular;
		
		    ambient *= attenuation;
		    diffuse *= attenuation;
		    specular *= attenuation;
		
		    return (ambient + diffuse + specular) * light.color;
		}

		vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) 
		{
		    vec3 lightDir = normalize(light.position - fragPos);
		    vec3 reflectDir = reflect(-lightDir, normal);
		
		    float distance = length(light.position - fragPos);
		    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
		    float theta = dot(lightDir, normalize(-light.direction));
		    float epsilon = light.cutoff - light.outerCutoff;
		    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
		
		    vec3 ambient = light.ambient * material.ambient;
		    vec3 diffuse = light.diffuse * max(dot(normal, lightDir), 0.0) * material.diffuse;
		    vec3 specular = light.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * material.specular;
		
		    ambient *= attenuation * intensity;
		    diffuse *= attenuation * intensity;
		    specular *= attenuation * intensity;
		
		    return (ambient + diffuse + specular) * light.color;
		}

void main()
{
	vec4 texColor = v_Color;

	switch(int(v_TexIndex))
	{
		case 0: texColor *= texture(u_Textures[0], v_TexCoord * v_TilingFactor); break;
		case 1: texColor *= texture(u_Textures[1], v_TexCoord * v_TilingFactor); break;
		case 2: texColor *= texture(u_Textures[2], v_TexCoord * v_TilingFactor); break;
		case 3: texColor *= texture(u_Textures[3], v_TexCoord * v_TilingFactor); break;
		case 4: texColor *= texture(u_Textures[4], v_TexCoord * v_TilingFactor); break;
		case 5: texColor *= texture(u_Textures[5], v_TexCoord * v_TilingFactor); break;
		case 6: texColor *= texture(u_Textures[6], v_TexCoord * v_TilingFactor); break;
		case 7: texColor *= texture(u_Textures[7], v_TexCoord * v_TilingFactor); break;
		case 8: texColor *= texture(u_Textures[8], v_TexCoord * v_TilingFactor); break;
		case 9: texColor *= texture(u_Textures[9], v_TexCoord * v_TilingFactor); break;
		case 10: texColor *= texture(u_Textures[10], v_TexCoord * v_TilingFactor); break;
		case 11: texColor *= texture(u_Textures[11], v_TexCoord * v_TilingFactor); break;
		case 12: texColor *= texture(u_Textures[12], v_TexCoord * v_TilingFactor); break;
		case 13: texColor *= texture(u_Textures[13], v_TexCoord * v_TilingFactor); break;
		case 14: texColor *= texture(u_Textures[14], v_TexCoord * v_TilingFactor); break;
		case 15: texColor *= texture(u_Textures[15], v_TexCoord * v_TilingFactor); break;
		case 16: texColor *= texture(u_Textures[16], v_TexCoord * v_TilingFactor); break;
		case 17: texColor *= texture(u_Textures[17], v_TexCoord * v_TilingFactor); break;
		case 18: texColor *= texture(u_Textures[18], v_TexCoord * v_TilingFactor); break;
		case 19: texColor *= texture(u_Textures[19], v_TexCoord * v_TilingFactor); break;
		case 20: texColor *= texture(u_Textures[20], v_TexCoord * v_TilingFactor); break;
		case 21: texColor *= texture(u_Textures[21], v_TexCoord * v_TilingFactor); break;
		case 22: texColor *= texture(u_Textures[22], v_TexCoord * v_TilingFactor); break;
		case 23: texColor *= texture(u_Textures[23], v_TexCoord * v_TilingFactor); break;
		case 24: texColor *= texture(u_Textures[24], v_TexCoord * v_TilingFactor); break;
		case 25: texColor *= texture(u_Textures[25], v_TexCoord * v_TilingFactor); break;
		case 26: texColor *= texture(u_Textures[26], v_TexCoord * v_TilingFactor); break;
		case 27: texColor *= texture(u_Textures[27], v_TexCoord * v_TilingFactor); break;
		case 28: texColor *= texture(u_Textures[28], v_TexCoord * v_TilingFactor); break;
		case 29: texColor *= texture(u_Textures[29], v_TexCoord * v_TilingFactor); break;
		case 30: texColor *= texture(u_Textures[30], v_TexCoord * v_TilingFactor); break;
		case 31: texColor *= texture(u_Textures[31], v_TexCoord * v_TilingFactor); break;

	}
	texColor.rgb *= vec3(gl_FragCoord.xy, 0.0);

        vec3 norm = normalize(v_Normal);

			vec3 viewDir = normalize(viewPos - FragPos);

		    vec3 resultDir = vec3(0.0);
			vec3 resultPoint = vec3(0.0);
			vec3 resultSpot = vec3(0.0);

	 for (int i = 0; i < numDirectionalLights; i++) 
			{
			    if (i >= MAX_DIRECTIONAL_LIGHTS)
				{
					break;
				}

			    resultDir += CalculateDirectionalLight(directionalLights[i], norm, viewDir);
			}

			for (int i = 0; i < numPointLights; i++) 
			{
			    if (i >= MAX_POINT_LIGHTS) 
				{
					break;
				}

			    resultPoint += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);
			}

			for (int i = 0; i < numSpotLights; i++) 
			{
			  if (i >= MAX_SPOT_LIGHTS) 
			  {
				break;
			  }

			  resultSpot += CalculateSpotLight(spotLights[i], norm, FragPos, viewDir);
			}

	vec3 result = resultDir + resultSpot + resultPoint;

	if (texColor.rgb != vec3(0.0))//No hace nada 
			{
				result *= texColor.rgb;
			}


	color = vec4(result,1.0f);
}
