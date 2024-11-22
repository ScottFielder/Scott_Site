#version 450
#extension GL_ARB_separate_shader_objects : enable
in vec2 uvCoordFromEval;
in vec3 normalFromEval;
out vec4 fragColor;
uniform sampler2D surfaceTextrure;
void main() {
    fragColor = texture(surfaceTextrure,uvCoordFromEval);
    //fragColor = vec4(1.0,1.0,1.0,1.0);
}