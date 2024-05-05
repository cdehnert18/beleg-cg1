#version 460 core

/*uniform*/ vec4 LightPosition = vec4(0, 0, 1, 1);  //Licht ist vor Kamera
/*uniform*/ vec4 EyeDirection = vec4(0, 0, -2, 1);  
/*uniform*/ vec4 ConeDirection = vec4(0, 0, -1, 1); 
/*vec3 Ambient = vec3(0.2, 0.2, 0.2);*/
uniform vec3 Ambient;
/*uniform*/ vec3 LightColor = vec3(0.7, 0.7, 0.7); 

/*uniform*/ float Shininess = 0.8;
/*uniform*/ float ConstantAttenuation = 0.1;
/*uniform*/ float LinearAttenuation = 0.5;
/*uniform*/ float QuadraticAttenuation = 0.8;
/*uniform*/ float SpotCosCutoff = 0.8;
/*uniform*/ float SpotExponent = 0.8;

in vec4 Position; 
in vec4 Color; 
in vec3 Normal; 
	
out vec4 fColor;

void main(){
	//Punktlicht
	vec3 lightDirection = vec3(LightPosition) - vec3(Position);
	float lightDistance = length(lightDirection);
	lightDirection = lightDirection / lightDistance;
	float attenuation = 1.0/(ConstantAttenuation + LinearAttenuation * lightDistance + QuadraticAttenuation * lightDistance * lightDistance);
	float spotCos = dot(lightDirection, -vec3(ConeDirection));
	if (spotCos < SpotCosCutoff) attenuation = 0.0;
	else attenuation *= pow(spotCos, SpotExponent);
	vec3 halfVector = normalize(lightDirection + vec3(EyeDirection));
	float diffuse = max(0.0, dot(Normal, lightDirection));
	float specular = max(0.0, dot(Normal, halfVector));
	if(diffuse <= 0.01)specular = 0.0; else specular = pow(specular,Shininess);
	vec3 scatteredLight = Ambient + LightColor * diffuse * attenuation;
	vec3 reflectedLight = LightColor * specular * attenuation;
	vec3 rgb = min(Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
	fColor = vec4(rgb, Color.a);
}