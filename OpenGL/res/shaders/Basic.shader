#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 Normal;

out vec2 v_TexCoord;
out vec3 NormalVer;
out vec3 worldPos0;

uniform mat4 u_MVP;
uniform mat4 gWorld;

void main()
{
   gl_Position = u_MVP * position;
   v_TexCoord = texCoord;
   NormalVer = (gWorld * vec4(Normal, 0.0)).xyz;
   worldPos0 = (gWorld * position).xyz;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 NormalVer;
in vec3 worldPos0;

struct DirectionalLight
{
	vec4 Color;
	float AmbientIntensity;
    float DiffuseIntensity;
    vec3 Direction;
};

uniform DirectionalLight gDirectionalLight;
uniform sampler2D u_Texture;
uniform vec3 gEyeWorldPos;

void main()
{
    float gSpecularPower = 1.0;
    vec4 texColor = texture2D(u_Texture, v_TexCoord);
    vec3 normal_ = normalize(NormalVer);

    vec4 ambientColor = gDirectionalLight.Color * gDirectionalLight.AmbientIntensity;

    float DiffuseFactor = dot(normal_, -gDirectionalLight.Direction);
    vec4 diffuseColor = vec4(0, 0, 0, 0);
    vec4 specularColor = vec4(0, 0, 0, 0);
    if (DiffuseFactor > 0)
    {
        diffuseColor = gDirectionalLight.Color * gDirectionalLight.DiffuseIntensity * DiffuseFactor;
    }
    vec3 VertexToEye = normalize(gEyeWorldPos - worldPos0);
    vec3 LightReflect = normalize(reflect(gDirectionalLight.Direction, normal_));
    float SpecularFactor = dot(VertexToEye, LightReflect);
    if (SpecularFactor > 0) {
        float gMatSpecularIntensity = 2.0f;
        specularColor = vec4(gDirectionalLight.Color) * gMatSpecularIntensity * SpecularFactor;
    }
    color = texColor * (ambientColor + diffuseColor + specularColor);
};