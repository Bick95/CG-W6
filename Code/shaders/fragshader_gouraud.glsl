#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec3 vertColor;
in vec2 textureCoords;

// Uniforms
uniform sampler2D sampler;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main()
{
    vec4 tColor = texture(sampler, textureCoords); // retrieve texture color

    fColor = vec4(vertColor.rgb, 1.0) * tColor; // color = illumination_intensity * texture_color
    // fColor = vec4(vertColor.rgb, 1.0); // without texture data

}
