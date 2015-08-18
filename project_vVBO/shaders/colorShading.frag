#version 120
//The fragment shader operates on each pixel in a given polygon
//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
varying vec4 fragColor; 


void main() {
    
    gl_FragColor = fragColor;
}