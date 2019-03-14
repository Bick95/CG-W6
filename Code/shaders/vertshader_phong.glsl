#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in; // Perform transformation operations on
layout (location = 1) in vec3 vertNormal_in;
layout (location = 2) in vec2 mesh_coords;

// Specify the Uniforms of the vertex shader
// uniform mat4 modelTransform; for example
uniform mat4 modelTransform;
uniform mat4 projectionTransform;
uniform mat3x3 preserveNormals;
uniform vec3 materialColor;
uniform vec3 materialCoeffs;
uniform vec3 lightColor;
uniform vec3 lightPos;

// Specify the output of the vertex stage


out vec3 vertNormal;
out vec3 color;
out vec3 coeffs;
out vec3 lColor;
out vec3 lPos;
out vec4 coordinates;
out vec2 textureCoords;

void main()
{
    gl_Position = vec4(vertCoordinates_in, 1.0);

    // Transform input vector
    gl_Position = projectionTransform*modelTransform*gl_Position; //4x4 * 4x1 = 4x1

    // Preserve Normals' original relative angles and normalize them
    vec3 normal = normalize(preserveNormals*vertNormal_in);

    vertNormal = normal;
    color = materialColor;
    coeffs = materialCoeffs;
    lColor = lightColor;
    lPos = lightPos;
    coordinates = gl_Position;
    textureCoords = mesh_coords;
}
