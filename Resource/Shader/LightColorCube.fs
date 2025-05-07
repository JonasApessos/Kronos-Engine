#version 460 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 LightPos;
uniform vec3 LightColor;
uniform vec3 ObjectColor;
uniform vec3 ObjectPos;

uniform vec3 ViewPos;

void main()
{
    float SpecularStrength = 0.5;
	float AmbientStrength = 0.1;
    vec3 Ambient = AmbientStrength * LightColor;

    vec3 Norm = normalize(Normal);
    vec3 LightDir = normalize(-LightPos);
    float Diff = max(dot(Norm, LightDir), 0.0);
    vec3 Diffuse = Diff * LightColor;

    vec3 ViewDir = normalize(ViewPos - FragPos);
    vec3 ReflectDir = reflect(-LightDir, Norm);

    float Spec = pow(Diff, 2);
    vec3 Specular = SpecularStrength * Spec * LightColor;

    float fDist = distance(LightPos, ObjectPos);
    vec3 Falloff = LightColor / (0.5 * fDist * fDist);

    vec3 Result = (Ambient + Diffuse + Specular) * ObjectColor * Falloff;

    FragColor = vec4(Result, 1.0);
}