#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec2 v_texCoord;
out vec3 shadNormal;

void main()
{
	glPosition = u_MVP * position;
	v_normal = (u_MVP * vec4(normal, 0.0)).xyz;
	v_texCoord = texCoord;
};

#shader fragmet
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;
in vec3 v_normal;

struct Material_ {
	sampler2D Diffuse;
	sampler2D Specular;
	float Schininess;
};

struct BaseLight
{
	vec4 Color;
	float AmbientIntensity;
	float DiffuseIntensity;
	float SpecularIntensity;
};

struct DirectLight
{
	BaseLight Base;
	vec3 Direction;
};

struct PointLight
{
	BaseLight Base;
	vec3 Position;

	struct {
		float Constant;
		float Linear;
		float Exp;
	} Atten;
};

uniform Material_ Material;
uniform mat4 Model;
uniform vec3 eyePos;
uniform unsigned int LIGHTS_DIR_COUNT;
uniform unsigned int LIGHTS_POINT_COUNT;
uniform PointLight m_pointLight[LIGHTS_COUNT];
uniform DirectLight m_directLight[LIGHTS_COUNT];

vec4 CalcDirLights(vec4 texDiffuse, vec4 texSpecular, vec3 normal, vec3 vertexToEye)
{
	vec4 color_out = texDiffuse;
	for (unsigned int i = 0; i < LIGHTS_DIR_COUNT; i++)
	{
		vec3 ambientColor = m_directLight[i].Base.Color * m_directLight[i].Base.AmbientIntensity;
		vec3 direction_n = normalize(-m_directLight[i].Direction);
		
		float diff_factor = dot(normal, direction_n);
		vec4 diffColor = vec4(0.0, 0.0, 0.0, 0.0);
		if (diff_factor > 0)
		{
			diffColor = m_directLight[i].Base.Color * m_directLight[i].Base.DiffuseIntensity * diff_factor;
		}

		vec3 reflectDir = normalize(reflect(-direction_n, normal));
		float spec_factor = dot(vertexToEye, reflectDir);
		vec4 specColor = vec4(0.0, 0.0, 0.0, 0.0);
		if (spec_factor > 0)
		{
			specColor = texSpecular * m_directLight[i].Base.Color * m_directLight[i].Base.SpecularIntensity * spec_factor;
		}

		color_out += (ambientColor + diffColor + specColor);
	}
	return color_out;
}

vec4 CalcPointLights(vec4 texDiffuse, vec4 texSpecular, vec3 normal, vec3 vertexToEye)
{
	vec4 color_out = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 diffColor = texture(Material.Diffuse, v_texCoord);
	vec4 specColor = texture(Material.Specular, v_texCoord);

	color = diffColor;
	
	for (unsigned int i = 0; i < LIGHTS_POINT_COUNT; i++)
	{
		vec3 ambientColor = m_directLight[i].Base.Color * m_pointLight[i].Base.AmbientIntensity;
		vec3 direction_n = normalize(-m_directLight[i].Direction);

		float diff_factor = dot(normal, direction_n);
		vec4 diffColor = vec4(0.0, 0.0, 0.0, 0.0);
		if (diff_factor > 0)
		{
			diffColor = m_pointLight[i].Base.Color * m_pointLight[i].Base.DiffuseIntensity * diff_factor;
		}

		vec3 reflectDir = normalize(reflect(-direction_n, normal));
		float spec_factor = dot(vertexToEye, reflectDir);
		vec4 specColor = vec4(0.0, 0.0, 0.0, 0.0);
		float Attenuation;
		if (spec_factor > 0)
		{
			float Distance = length(m_pointLight[i].Position - FragPos);
			specColor = texSpecular * m_pointLight[i].Color * m_pointLight[i].Base.SpecularIntensity * spec_factor;
			float Attenuation = m_pointLight[i].Atten.Constant +
				m_pointLight[i].Atten.Linear * Distance +
				m_pointLight[i].Atten.Exp * Distance * Distance;
			specColor /= Attenuation;
		}

		color_out += (ambientColor + diffColor + specColor);
	}

	return color_out;
};

void main()
{
	float pos = 0;
	vec4 texDiffuse = texture(Material.Diffuse);
	vec4 texSpecular = texture(Material.Specular);
	vec3 normal = normalize(v_normal);
	vec4 vertexToEye = normalize(eyePos - pos);
	vec4 dirColor   = CalcDirLights  (texDiffuse, texSpecular, normal, vertexToEye);
	vec4 pointColor = CalcPointLights(texDiffuse, texSpecular, normal, vertexToEye);
	color = texDiffuse * (dirColor + pointColor);
};