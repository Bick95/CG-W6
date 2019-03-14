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
uniform mat3 preserveNormals;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 materialColor;
uniform vec3 coeffs;


// Specify the output of the vertex stage
out vec3 vertColor;
out vec2 textureCoords;

void main()
{
    gl_Position = vec4(vertCoordinates_in, 1.0);

    // Transform input vector
    gl_Position = projectionTransform*modelTransform*gl_Position; //4x4 * 4x1 = 4x1


    // Illumination calculation
    int p = 3;

    float ka = coeffs[0];
    float kd = coeffs[1];
    float ks = coeffs[2];

    vec3 eye_pos = vec3(0,0,0);

    // Transform object
    vec4 object_transformed = modelTransform*vec4(vertCoordinates_in, 1.0);

    // Preserve Normals' original relative angles and normalize them
    vec3 normal = normalize(preserveNormals*vertNormal_in);

    // Compute further vector
    vec3 hit_point = vec3(object_transformed.xyz); // hit_point from transformed input coords
    vec3 V = normalize(eye_pos - hit_point);
    vec3 L = normalize(lightPos - hit_point); // Light position doesn't get transformed to hold it stable at a (fixed) point in the scene
    vec3 R = normalize(2*dot(normal,L) * normal - L);

    // Compute color-components
    vec3 ambient = materialColor * ka;
    vec3 diffuse = max(0,dot(normal,L)) * materialColor * lightColor * kd;
    vec3 specular = pow(max(0,dot(V, R)), p) * lightColor * ks;

    vec3 light = ambient + diffuse + specular;

    // Pass to fragment shader
    vertColor =  light;
    textureCoords = mesh_coords;
}
