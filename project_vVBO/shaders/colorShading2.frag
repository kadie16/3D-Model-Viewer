#version 120
//The fragment shader operates on each pixel in a given polygon
//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
varying vec3 position; 
varying vec4 fragColor;
varying vec3 normal; 

uniform vec3 lightPos;

uniform vec3 mAmbient; 
uniform vec3 mDiffuse; 
uniform vec3 mSpecular;
uniform float shininess;

uniform vec3 lAmbient; 
uniform vec3 lDiffuse; 
uniform vec3 lSpecular;

void main() {
	
    vec3 ambient = mAmbient * lAmbient; 
    vec3 surface2light = normalize(lightPos - position);
    vec3 norm = normalize(normal);
    // If less than 0, return 0
    float diffuseContribution = max(0.0, dot(norm, surface2light)); 
    vec3 diffuse = diffuseContribution*mDiffuse*lDiffuse;
    vec3 surface2view = normalize(-position);
    vec3 reflection = reflect(-surface2light, norm);
    float specularContribution = max(0.0, dot(surface2view, reflection));
    vec3 specular = specularContribution * mSpecular * lSpecular;
    gl_FragColor = vec4(ambient+diffuse+specular,1.0)*fragColor;

}