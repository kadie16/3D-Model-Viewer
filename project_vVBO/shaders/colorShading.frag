#version 120
//The fragment shader operates on each pixel in a given polygon

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.

void main() {
    //Just hardcode the color to red
    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}