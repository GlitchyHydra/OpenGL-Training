#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal_position;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    sampler2D diffuseTex;
    sampler2D specularTex;
};

layout(location = 0) out vec4 color;

in vec3 v_color;
in vec3 v_normal;
in vec2 v_TexCoord;

uniform Material material;

uniform vec3 lightPos0;
uniform vec3 cameraPos;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

vec3 calculateAmbient(Material material)
{
    return material.ambient;
}

void main()
{
    vec3 ambientFinal = calculateAmbient(material)
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
    
};