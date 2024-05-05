#version 460 core  // 420, 330 core , compatibility

//Ambientes Licht
uniform vec3 Ambient; 

//Richtungslicht
uniform vec3 LightColor; 

vec4 LightDirection = vec4(0,0,1,1); 
vec3 EyeDirection = vec3(0,0,-1); 
float Shininess=0.8;

in vec4 Color; 
in vec3 Normal;

out vec4 fColor;

void main() {
	
	//Ambientes Licht
	//vec3 scatteredLight = Ambient;
	//vec3 rgb = min(Color.rgb * scatteredLight, vec3(1.0)); 
	//fColor = vec4(rgb, Color.a); 
	
	
	
	//Richtungslicht
	vec3 lDirection = normalize(vec3(LightDirection));
	float diffuse = max(0.0, dot(Normal, lDirection));
	vec3 halfVector = normalize(lDirection + (vec3(EyeDirection)));
	float specular = max(0.0,dot(Normal, halfVector));
	if (diffuse <= 0.01) specular = 0.0; else specular = pow(specular, 0.2);
	
	//Ambientes Licht und Richtungslicht
	vec3 scatteredLight = Ambient + LightColor * diffuse;
	//vec3 scatteredLight = LightColor * diffuse;

	vec3 reflectedLight = LightColor * specular;
	vec3 rgb = min(Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
	fColor = vec4(rgb,Color.a);

	//fColor = Color;
	
}
