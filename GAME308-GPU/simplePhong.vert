#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in  vec4 vVertex;
layout (location = 1) in  vec4 vNormal;
layout (location = 2) in  vec2 texCoords;

layout(binding = 0) uniform UniformBufferObject {
    mat4 modelMatrix;
    mat4 viewMatrix;
    mat4 projectionMatrix;
	vec4 lightPos;
} ubo;

layout (location = 0) out vec3 vertNormal;
layout (location = 1) out vec3 lightDir;
layout (location = 2) out vec3 eyeDir;
layout (location = 3) out vec2 fragTexCoords;


void main() {
	fragTexCoords = texCoords;
	/// We must fix this, just load the normalMatrix in to the UBO
	mat3 normalMatrix = mat3(transpose(inverse(ubo.modelMatrix)));

	vertNormal = normalize(normalMatrix * vNormal.xyz); /// Rotate the normal to the correct orientation 
	vec3 vertPos = vec3(ubo.viewMatrix * ubo.modelMatrix * vVertex); /// This is the position of the vertex from the origin
	vec3 vertDir = normalize(vertPos);
	eyeDir = -vertDir;
	lightDir = normalize(vec3(ubo.lightPos) - vertPos); /// Create the light direction.
	
	gl_Position =  ubo.projectionMatrix * ubo.viewMatrix * ubo.modelMatrix * vVertex; 
}
