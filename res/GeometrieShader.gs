#version 430 core

layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;

in vec4 gColor[];
in vec3 gPosition[];
in vec3 gNormal[];

out vec4 Color;
out vec3 Normal;
out vec3 Position;


void main() {
    /*
    if ((gl_PrimitiveIDIn&1) > 0) {
        for(int n = 0; n < gl_in.length(); n++) {
            gl_Position = gl_in[n].gl_Position;
            Color = gColor[n];
            Position = gPosition[n];
            Normal = gNormal[n];
            EmitVertex();
        }
        EndPrimitive(); 
    }
    
    for(int n = 0; n < gl_in.length(); n++) {
        gl_Position = gl_in[n].gl_Position + 1;
        Position = gPosition[n] + 1;
        Color = gColor[n] + 0.5;
        Normal = gNormal[n];
        EmitVertex();
    }
    EndPrimitive(); 
    */

    for(int n = 0; n < gl_in.length(); n++) {
        gl_Position = gl_in[n].gl_Position;
        Color = gColor[n];
        Position = gPosition[n];
        Normal = gNormal[n];
        EmitVertex();
    }
    
    for(int n = 0; n < gl_in.length(); n++) {
        gl_Position = gl_in[n].gl_Position + 1;
        Position = gPosition[n] + 1;
        Color = gColor[n] + 0.5;
        Normal = gNormal[n];
        EmitVertex();
    }
    EndPrimitive();

}