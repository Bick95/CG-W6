#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in; // Perform transformation operations on
layout (location = 1) in vec3 vertNormal_in;
layout (location = 2) in vec2 uv_coords_in; //mesh_coords

// Specify the Uniforms of the vertex shader
// uniform mat4 modelTransform; for example
uniform mat4 modelTransform;
uniform mat4 projectionTransform;
uniform mat4 viewTransform;
uniform mat3x3 preserveNormals;


// Specify the output of the vertex stage
out vec2 uv;

void main()
{
    gl_Position = vec4(vertCoordinates_in, 1.0);
    //position[2] = position[0]%0.2;

    // Transform input vector -- Check again
    gl_Position = projectionTransform*viewTransform*modelTransform*gl_Position;

    // Set output
    uv = vec2(uv_coords_in[0], uv_coords_in[1]);
}
