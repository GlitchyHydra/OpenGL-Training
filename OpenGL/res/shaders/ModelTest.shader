#shader vertex
#version 330 core

layout(location = 0) in vec4 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 texCoord;

out vec2 v_texCoord;
out vec3 v_normal;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * Position;
	v_normal = (u_MVP * vec4(Normal, 0.0)).xyz;
	v_texCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;
in vec3 v_normal;

struct Material_ {
	sampler2D Diffuse;
	sampler2D Specular;
	float Schininess;
};

uniform Material_ Material;

void main()
{
	float pos = 0;
	vec4 texDiffuse = texture(Material.Diffuse, v_texCoord);
	vec4 texSpecular = texture(Material.Specular, v_texCoord);
	vec3 normal = normalize(v_normal);
	color = texDiffuse;
};