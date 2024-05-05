#version 430 core  // 420, 330 core , compatibility

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model; 
uniform mat3 NormalMatrix;

layout (location=0) in vec4 vPosition;
layout (location=1) in vec4 vColor;
layout (location=2) in vec3 vNormal;
layout (location=3) in vec2 vTexture;

out vec4 Color;
out vec3 Normal;
out vec3 Position;
out vec2 vs_tex_coord;

void main() {
	gl_Position = projection * view * model * vPosition;
	Position = vec3(vPosition);
	Normal = normalize(NormalMatrix * vNormal);
	Color = vColor;
	vs_tex_coord=vTexture;
}