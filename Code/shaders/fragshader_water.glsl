#version 330 core


// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec3 normals;
in vec4 coordinates;

uniform vec3 color;
uniform vec3 coeffs;
// assumption: there is only 1 light source
uniform vec3 lColor;
uniform vec3 lPos;



// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
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
    vec3 normal = normals;
    // Compute further vector

    vec3 V = normalize(eye_pos - hit_point);
    // lightpos input gets normalized, need to multiply by 10 to be the same as in gouraoud
    vec3 L = normalize(lPos - hit_point);
    vec3 R = normalize(2*dot(normal,L) * normal - L);

    // Compute color-components
    vec3 ambient = color * ka;
    vec3 diffuse = max(0,dot(normal,L)) * color * lColor * kd;
    vec3 specular = pow(max(0,dot(V, R)), p) * lColor * ks;

    vec3 fColor = ambient + diffuse + specular ;
    col =  vec4(smoothstep(0.8, 0.95,mix(0,1,fColor[0])),smoothstep(0.8, 0.95, mix(0.467,1,fColor[1])), smoothstep(0.8, 0.95, mix(0.745,1,fColor[2])), 1 );
}
