#version 120
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 3 floats
attribute vec3 vertexPosition;
attribute vec4 vertexColor; 
varying vec4 fragColor;

void main() {
    //Set the x,y position on the screen
    gl_Position.xyz = vertexPosition;
    
    //Indicate that the coordinates are normalized
    gl_Position.w = 1.0;
    fragColor = vertexColor; 
}