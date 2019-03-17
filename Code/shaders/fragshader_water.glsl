#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec2 uv;


// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main()
{
    //fColor = vec4(uv[0], uv[1], 0.0, 1.0);
    fColor = vec4(1, 1, 1, 0.5);
}