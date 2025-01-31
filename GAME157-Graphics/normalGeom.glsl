#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) uniform mat4 projectionMatrix;
layout(location = 1) uniform mat4 viewMatrix;
layout(location = 2) uniform mat4 modelMatrix;
layout(location = 3) uniform vec4 color;

layout (triangles) in;
layout (line_strip, max_vertices = 2) out; /// output is lines w/ 6 verticies

in VertexStage {
	vec3 normal;
} gs_in[];

void main() {
	float length = color.w; /// use w to hold the length of the normal 

	for(int i = 0; i<3; ++i){
		/// This is the base position of the normal
		gl_Position = projectionMatrix * gl_in[i].gl_Position; 
		EmitVertex();

		/// Now, following the normals direction, move length distance away and form the head of the normal 
		gl_Position = projectionMatrix * (gl_in[i].gl_Position + vec4(gs_in[i].normal, 1.0) * length);
		EmitVertex();

		EndPrimitive(); 
	}
	

}