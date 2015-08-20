#version 120
//The fragment shader operates on each pixel in a given polygon
//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
varying vec3 position; 
varying vec4 fragColor;
float shininess;
varying vec3 normal;
varying vec3 vertex_to_light_vector;
 
void main()
{
	shininess = 2.0;
	const vec4 AmbientColor = vec4(0.1, 0.1, 0.1, 1.0);
    // Calculating The Diffuse Term 
 	float DiffuseTerm = pow(max(0.0, dot(normal, vertex_to_light_vector)),shininess);
    // Calculating The Final Color
    gl_FragColor = (fragColor + AmbientColor) * DiffuseTerm;
}