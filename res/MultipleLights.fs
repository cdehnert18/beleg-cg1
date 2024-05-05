#version 460 core

struct LightProperties {
	bool isEnabled; 
	bool isLocal; 
	bool isSpot; 
	vec3 ambient; 
	vec3 color;
	vec4 position; 
	vec4 coneDirection; 
	float spotCosCutoff; 
	float spotExponent;
	float constantAttenuation; 
	float linearAttenuation; 
	float quadraticAttenuation;
};

struct MaterialProperties {
	vec3 emission; 
	vec3 ambient; 
	vec3 diffuse; 
	vec3 specular; 
	float shininess;
	float transparency; 
};

const int MaxLights = 10; 
uniform LightProperties Lights[MaxLights];

const int NumMaterials = 14; 
uniform MaterialProperties Material[NumMaterials];

vec3 scatteredLight=vec3(0,0,0); 
vec3 reflectedLight=vec3(0,0,0);

flat in int MatIndex;

out vec4 fColor;

void main() {
	for (int light=0;light<MaxLights;++light) {
		float attenuation, diffuse, specular; ...
		scatteredLight += Lights[light].ambient*Material[MatIndex].ambient*attenuation+  Lights[light].color*Material[MatIndex].diffuse*diffuse*attenuation;
		reflectedLight += Lights[light].color*Material[MatIndex].specular*specular*attenuation; 
	}
	vec3 rgb = min(Material[MatIndex].emission+scatteredLight+reflectedLight, vec3(1.0));
	fColor = vec4(rgb,Material[MatIndex].transparency); 
}