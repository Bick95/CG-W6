#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec3 vertNormal;
in vec3 color;
in vec3 coeffs;
// assumption: there is only 1 light source
in vec3 lColor;
in vec3 lPos;
in vec4 gl_FragCoord ;
// Specify the Uniforms of the fragment shaders
// uniform vec3 lPosition; // for example
uniform mat4 modelTransform;
uniform mat4 projectionTransform;
uniform int width;
uniform int height;
uniform vec3 lightPos;
uniform sampler2D sampler;

in vec4 coordinates;
in vec2 textureCoords;

out vec4 col;

void main()
{


    // Illumination calculation
    int p = 3;

    float ka = coeffs[0];
    float kd = coeffs[1];
    float ks = coeffs[2];

    // assumption: view is always at 0,0,0
    vec3 eye_pos = vec3(0,0,0);
    //vec4 coordinates = vec4(gl_FragCoord[0]/width, gl_FragCoord[1]/height, gl_FragCoord[2], gl_FragCoord[3]);
    vec4 object_transformed = coordinates;
    vec3 hit_point = vec3(object_transformed.xyz); // hit_point from transformed pos coords
    vec3 normal = vertNormal;
    // Compute further vector

    vec3 V = normalize(eye_pos - hit_point);
    // lightpos input gets normalized, need to multiply by 10 to be the same as in gouraoud
    vec3 L = normalize(lightPos - hit_point);
    vec3 R = normalize(2*dot(normal,L) * normal - L);

    // Compute color-components
    vec3 ambient = color * ka;
    vec3 diffuse = max(0,dot(normal,L)) * color * lColor * kd;
    vec3 specular = pow(max(0,dot(V, R)), p) * lColor * ks;

    vec4 tColor = texture(sampler, textureCoords);
    vec3 fColor = ambient + diffuse + specular ;
    col =  vec4(fColor, 1.0) *tColor;

    /// output for non texture version
    // col = fColor;
}
