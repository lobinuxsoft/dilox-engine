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

	float ambientStrength = 1.0f;
	vec4 ambient = ambientStrength * u_LightColor;            

	  vec3 norm = normalize(v_Normal);                       
      vec3 lightDir = normalize( u_LightPosition - FragPos);         
      float diff = max(dot(norm, lightDir), 0.0);            
      vec4 diffuseLight = diff *  u_LightColor;                 


	vec4 result = (ambient + diffuseLight) * texColor;


	color = result;
}
