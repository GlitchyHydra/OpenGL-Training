#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 Normal;

out vec2 v_TexCoord;
out vec3 NormalVer;

uniform mat4 u_MVP;
uniform mat4 gWorld;

void main()
{
   gl_Position = u_MVP * position;
   v_TexCoord = texCoord;
   NormalVer = (gWorld * vec4(Normal, 0.0)).xyz;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 NormalVer;

struct DirectionalLight
{
	vec4 Color;
	float AmbientIntensity;
    float DiffuseIntensity;
    vec3 Direction;
};

uniform DirectionalLight gDirectionalLight;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture2D(u_Texture, v_TexCoord);
    vec4 ambientColor = gDirectionalLight.Color * gDirectionalLight.AmbientIntensity;
    float DiffuseFactor = dot(normalize(NormalVer), -gDirectionalLight.Direction);
    vec4 diffuseColor;
    if (DiffuseFactor > 0)
    {
        diffuseColor = gDirectionalLight.Color * gDirectionalLight.DiffuseIntensity * DiffuseFactor;
    }
    else
    {
        diffuseColor = vec4(0, 0, 0, 0);
    }
    color = texColor * (ambientColor + diffuseColor);
};