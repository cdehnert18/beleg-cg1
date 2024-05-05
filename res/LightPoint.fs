#version 430 core  // 420, 330 core , compatibility

const int MAX_POINT_LIGHTS = 2;

uniform bool isTexture;
vec3 gCameraLocalPos = vec3(0, 0, 0);
in vec2 vs_tex_coord;
uniform sampler2D tex;

in vec4 Color;
in vec3 Normal;
in vec3 Position;

out vec4 fColor;

vec4 myColor = Color;

struct BaseLight
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
};

struct DirectionalLight
{
    BaseLight Base;
    vec3 Direction;
};

struct Attenuation
{
    float Constant;
    float Linear;
    float Exp;
};

struct PointLight
{
    BaseLight Base;
    vec3 LocalPos;
    Attenuation Atten;
};


struct Material
{
    vec3 AmbientColor;
    vec3 DiffuseColor;
    vec3 SpecularColor;
};

DirectionalLight gDirectionalLight = DirectionalLight(BaseLight(vec3(0.8, 0.8, 0.8), 0.2, 0.8), vec3(0, 0, -1));

int gNumPointLights = 2;

PointLight gPointLights[MAX_POINT_LIGHTS] = PointLight[](
    PointLight(BaseLight(vec3(1.0, 0.0, 0.0), 0.2, 0.8), vec3(-2.0, 0.5, 0.0), Attenuation(1.0, 0.1, 0.01)),
    PointLight(BaseLight(vec3(0.0, 0.0, 1.0), 0.2, 0.8), vec3(2.0, 0.5, 0.0), Attenuation(1.0, 0.1, 0.01))
);

Material gMaterial = Material(vec3(0.9, 0.2, 0.2), vec3(0.8, 0.8, 0.8), vec3(0.2, 0.2, 0.2));

vec4 CalcLightInternal(BaseLight Light, vec3 LightDirection, vec3 Normal)
{
    vec4 AmbientColor = vec4(Light.Color, 1.0f) * Light.AmbientIntensity * vec4(gMaterial.AmbientColor, 1.0f);

    float DiffuseFactor = dot(Normal, -LightDirection);

    vec4 DiffuseColor = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);

    if (DiffuseFactor > 0) {
        DiffuseColor = vec4(Light.Color, 1.0f) * Light.DiffuseIntensity * vec4(gMaterial.DiffuseColor, 1.0f) * DiffuseFactor;

        vec3 PixelToCamera = normalize(gCameraLocalPos - Position);
        vec3 LightReflect = normalize(reflect(LightDirection, Normal));
        float SpecularFactor = dot(PixelToCamera, LightReflect);
        if (SpecularFactor > 0) {
            float SpecularExponent = 32.0;
            SpecularFactor = pow(SpecularFactor, SpecularExponent);
            SpecularColor = vec4(Light.Color, 1.0f) * Light.DiffuseIntensity * vec4(gMaterial.SpecularColor, 1.0f) * SpecularFactor;
        }
    }

    return (AmbientColor + DiffuseColor + SpecularColor);
}

vec4 CalcDirectionalLight()
{
    vec4 LightDirection = vec4(0,0,1,1); 
    vec3 EyeDirection = vec3(0,0,-1);

    vec3 lDirection = normalize(vec3(LightDirection));
	float diffuse = max(0.0, dot(Normal, lDirection));
	vec3 halfVector = normalize(lDirection + (vec3(EyeDirection)));
	float specular = max(0.0,dot(Normal, halfVector));
	if (diffuse <= 0.01) specular = 0.0; else specular = pow(specular, 0.2);
	vec3 scatteredLight = gDirectionalLight.Base.Color * diffuse;
	vec3 reflectedLight = gDirectionalLight.Base.Color * specular;
	vec3 rgb = min(myColor.rgb * scatteredLight + reflectedLight, vec3(1.0));
	
    return vec4(rgb, myColor.a);
}

vec4 CalcPointLight(int Index, vec3 Normal)
{
    vec3 LightDirection = Position - gPointLights[Index].LocalPos;
    float Distance = length(LightDirection);
    LightDirection = normalize(LightDirection);

    vec4 ColorP = CalcLightInternal(gPointLights[Index].Base, LightDirection, Normal);
    float Attenuation =  gPointLights[Index].Atten.Constant + gPointLights[Index].Atten.Linear * Distance + gPointLights[Index].Atten.Exp * Distance * Distance;

    return ColorP / Attenuation;
}

void main()
{
    if(isTexture == true) {
        myColor = texture(tex, vs_tex_coord);
    }

    vec4 TotalLight = vec4(0.1, 0.1, 0.1, 0.1);
    TotalLight += CalcDirectionalLight();

    for (int i = 0 ; i < gNumPointLights ; i++) {
        TotalLight += CalcPointLight(i, Normal);
    }

    fColor = vec4(vec3(TotalLight), myColor.a);
    //fColor = myColor;
    //fColor = vec4(Normal, 1);
}