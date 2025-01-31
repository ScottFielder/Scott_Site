#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 3) uniform vec4 color;
layout(location = 0) out vec4 fragColor;

void main() {
    vec4 theNormalsColor = color;
    /// Remember that the w component of the color is the length of the drawn normalize
    /// Just set it to be zero 
    theNormalsColor.w = 0.0;
    fragColor = theNormalsColor;
}