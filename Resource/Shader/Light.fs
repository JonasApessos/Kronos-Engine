#version 450 core

struct FSpotLight
{
    vec3 Position;
    vec3 Direction;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    float Intensity;
    float Linear;
    float Quadratic;
    float CutOff;
    float OuterCutOff;
};

struct FPointLight
{
    vec3 Position;
    vec3 Direction;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    float Intensity;
    float Constant;
    float Linear;
    float Quadratic;
};

struct FDirectionalLight
{
    vec3 Direction;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    float Intensity;
};

struct FMaterial
{
    vec3 Diffuse;
    vec3 Specular;
    float Shininess;
};

struct FTexMaterial
{
    sampler2D Diffuse;
    sampler2D Specular;
    float Shininess;
};

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

#define NR_POINT_LIGHTS 4

uniform FDirectionalLight DirLight;
uniform FPointLight PointLights[NR_POINT_LIGHTS];
uniform FMaterial Material;
uniform FTexMaterial TexMaterial;

uniform vec3 ViewPos;

float QuadraticInverseAttenuation(in float InfIntensity, in float InfDistance)
{
    return (InfIntensity / (4 * 3.14 * pow(InfDistance, 2) + InfIntensity));
}

float LinearInverseAttenuation(in float InfIntensity, in float InfDistance)
{
    return (InfIntensity / (InfIntensity + InfDistance));
}

float SpotLightIntensity(in FSpotLight InrSpotLight, in vec3 InrLightDir)
{
    float Theta = dot(InrLightDir, normalize(-InrSpotLight.Direction));
    float Epsilon = InrSpotLight.CutOff - InrSpotLight.OuterCutOff;
    float Intensity = clamp((Theta - InrSpotLight.OuterCutOff) / Epsilon, 0.0, 1.0);

    return Intensity;
}

float PointLightAttenuation(in FPointLight InrPointLight, in float InfDistance)
{
    return (InrPointLight.Intensity / (InrPointLight.Constant + InrPointLight.Linear * InfDistance + InrPointLight.Quadratic * pow(InfDistance, 2)));
}

float PointLightAttenuation(in FSpotLight InrSpotLight, in float InfDistance)
{
    return (InrSpotLight.Intensity / (InrSpotLight.Intensity + InrSpotLight.Linear * InfDistance + InrSpotLight.Quadratic * pow(InfDistance, 2)));
}

//Diffuse Directional Calc
vec3 Diffuse(in FDirectionalLight InrDirLight, in FTexMaterial InrMat, in vec3 InrNormal, in vec3 InrLightDir)
{
    float Diff = max(dot(InrNormal, InrLightDir), 0.0);

    vec4 TexColor = texture(InrMat.Diffuse, TexCoords);

    if(TexColor.a < 0.1)
        discard;

    vec3 DiffuseResult = InrDirLight.Diffuse * Diff * texture(InrMat.Diffuse, TexCoords).rgb;

    return DiffuseResult;
}

//Diffuse Spot Calc
vec3 Diffuse(in FSpotLight InrSpotLight, in FTexMaterial InrMat, in vec3 InrNormal, in vec3 InrLightDir)
{
    float Diff = max(dot(InrNormal, InrLightDir), 0.0);

    return InrSpotLight.Diffuse * Diff * texture(InrMat.Diffuse, TexCoords).rgb;
}

//Diffuse Point Calc
vec3 Diffuse(in FPointLight InrPointLight, in FTexMaterial InrMat, in vec3 InrNormal, in vec3 InrLightDir)
{
    float Diff = max(dot(InrNormal, InrLightDir), 0.0);

    return InrPointLight.Diffuse * Diff * texture(InrMat.Diffuse, TexCoords).rgb;
}

//Specular Directional Calc
vec3 Specular(in FDirectionalLight InrDirLight, in FTexMaterial InrMat, in vec3 InrNormal, in vec3 InrViewDir, in vec3 InrLightDir)
{
    vec3 ReflectDir = reflect(-InrLightDir, InrNormal);
    float Spec = pow(max(dot(InrViewDir, ReflectDir), 0.0), InrMat.Shininess);

    return InrDirLight.Specular * Spec * texture(InrMat.Specular, TexCoords).rgb;
}

//Specular Spot Calc
vec3 Specular(in FSpotLight InrSpotLight, in FTexMaterial InrMat, in vec3 InrNormal, in vec3 InrViewDir, in vec3 InrLightDir)
{
    vec3 ReflectDir = reflect(-InrLightDir, InrNormal);
    float Spec = pow(max(dot(InrViewDir, ReflectDir), 0.0), InrMat.Shininess);

    return InrSpotLight.Specular * Spec * texture(InrMat.Specular, TexCoords).rgb;
}

//Specular Point Calc
vec3 Specular(in FPointLight InrPointLight, in FTexMaterial InrMat, in vec3 InrNormal, in vec3 InrViewDir, in vec3 InrLightDir)
{
    vec3 ReflectDir = reflect(-InrLightDir, InrNormal);
    float Spec = pow(max(dot(InrViewDir, ReflectDir), 0.0), InrMat.Shininess);

    return InrPointLight.Specular * Spec * texture(InrMat.Specular, TexCoords).rgb;
}

//Ambient Directional Calc
vec3 Ambient(in FDirectionalLight InrDirLight, in FTexMaterial InrMat)
{
    return InrDirLight.Ambient * texture(InrMat.Diffuse, TexCoords).rgb;
}

//Ambient Spot Calc
vec3 Ambient(in FSpotLight InrSpotLight, in FTexMaterial InrMat)
{
    return InrSpotLight.Ambient * texture(InrMat.Diffuse, TexCoords).rgb;
}

//Ambient Point Calc
vec3 Ambient(in FPointLight InrPointLight, in FTexMaterial InrMat)
{
    return InrPointLight.Ambient * texture(InrMat.Diffuse, TexCoords).rgb;
}


//Directional Light Calc
vec3 CalcDirLight(in FDirectionalLight InrDirLight, in vec3 InrNormal, in vec3 InrViewDir)
{
    vec3 LightDir = normalize(-InrDirLight.Direction);

    vec3 Diffuse = Diffuse(InrDirLight, TexMaterial, InrNormal, LightDir);
    vec3 Specular = Specular(InrDirLight, TexMaterial, InrNormal, InrViewDir, LightDir);
    vec3 Ambient = Ambient(InrDirLight, TexMaterial);

    return Ambient + Diffuse + Specular;
}


//Point Light Calc
vec3 CalcPointLight(in FPointLight InrPointLight, in vec3 InrNormal, in vec3 InrFragPos, in vec3 InrViewDir)
{
    vec3 LightDir = normalize(InrPointLight.Position - FragPos);

    float Distance = length(InrPointLight.Position - InrNormal);
    float Attenuation = PointLightAttenuation(InrPointLight, Distance);

    vec3 Diffuse = Attenuation * Diffuse(InrPointLight, TexMaterial, InrNormal, LightDir);
    vec3 Specular = Attenuation * Specular(InrPointLight, TexMaterial, InrNormal, InrViewDir, LightDir);
    vec3 Ambient = Attenuation * Ambient(InrPointLight, TexMaterial);

    return Ambient + Diffuse + Specular;
}

//Spot Light Calc
vec3 CalcSpotLight(in FSpotLight InrSpotLight, in vec3 InrNormal, in vec3 InrViewDir)
{
    vec3 LightDir = normalize(InrSpotLight.Position - FragPos);

    float Distance = length(LightDir - InrNormal);
    float Attenuation = QuadraticInverseAttenuation(InrSpotLight.Intensity, Distance);
    float Intensity = SpotLightIntensity(InrSpotLight, LightDir);

    vec3 Diffuse = Attenuation * Intensity * Diffuse(InrSpotLight, TexMaterial, InrNormal, LightDir);
    vec3 Specular = Attenuation * Intensity * Specular(InrSpotLight, TexMaterial, InrNormal, InrViewDir, LightDir);
    vec3 Ambient = Attenuation * Ambient(InrSpotLight, TexMaterial);

    return Ambient + Diffuse + Specular;
}

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float Depth)
{
    float Z = Depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - Z * (far - near));
}

void main()
{
    vec3 Norm = normalize(Normal);
    vec3 ViewDir = normalize(ViewPos - FragPos);

    vec3 Result = CalcDirLight(DirLight, Norm, ViewDir);

    FragColor = vec4(Result, 1.0);
}