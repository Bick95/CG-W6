#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in; // Perform transformation operations on
layout (location = 1) in vec3 vertNormal_in;
layout (location = 2) in vec2 uv_coords_in;

// Specify the Uniforms of the vertex shader
// uniform mat4 modelTransform; for example
uniform mat4 modelTransform;
uniform mat4 projectionTransform;
uniform mat4 viewTransform;
uniform mat3x3 preserveNormals;
uniform float timeCoeff;
uniform vec3 wave2;
uniform vec3 wave3;
uniform vec3 wave1;

uniform int numWaves;
uniform vec3 amplitude[];
uniform vec3 frequency[];
uniform vec3 phase[];

uniform float amplitudes[3];
uniform float frequencies[3];
uniform float phases[3];

float waveHeight1(in float u){
    float height = 0;
    for (int i = 0; i < 3; i++){
        height += amplitudes[i] * sin(2*3.141593 * (frequencies[i] * u + timeCoeff + phases[i]));
    }
    return height;
}

float waveHeight(in float u, vec3 wave ){ // take wave out; it's kinda obsolete
    float height = wave[0] * sin(2*3.141593 * (wave[1] * u + timeCoeff + wave[2]));
    return height;
}

float waveDU1(in float u){ // take wave out; it's kinda obsolete
    float height = 0;
    for (int i = 0; i < 3; i++){
        height += amplitudes[i] * cos(2*3.141593 * (frequencies[i] * u + timeCoeff + phases[i])) * frequencies[i] * 2*3.141593 ;
    }
    return height;
}

float waveDU(in float u, vec3 wave ){ // take wave out; it's kinda obsolete
    float height = wave[0] * cos(2*3.141593 * (wave[1] * u + timeCoeff + wave[2])) * wave[1] * 2*3.141593 ;
    return height;
}

// Specify the output of the vertex stage
out vec4 coordinates;
out vec3 normals;

void main()
{
    vec4 position = vec4(vertCoordinates_in, 1.0);

    // Suggestion: (doesn't work yet)
    //position.z = waveHeight1(position.x);
    //normals = normalize(vec3(-waveDU1(position.x), 0.0, 1.0));

    // Working version
    position.z =  waveHeight(position.x, wave1) + waveHeight(position.x, wave2) +  waveHeight(position.x, wave3);
    //normals = normalize(vec3( - waveDU(position.x, wave1), 0, 1.0) + vec3( - waveDU(position.x, wave2), 0, 1.0) + vec3( - waveDU(position.x, wave3), 0, 1.0));
    normals = normalize(vec3(- waveDU(position.x, wave1) - waveDU(position.x, wave2) - waveDU(position.x, wave3), 0, 1.0));

    // Transform input vector
    coordinates = modelTransform*position;
    gl_Position = projectionTransform*viewTransform*modelTransform*position;


}


