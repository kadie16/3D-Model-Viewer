#version 120
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 3 floats
attribute vec3 vertexPosition;
attribute vec4 vertexColor; 
//attribute vec3 vertexNormal;
varying vec4 fragColor;

void main() {
    //Set the x,y position on the screen

    gl_Position.xyz = vertexPosition;
    //gl_Normal.xyz = vertexNormal;
    //Indicate that the coordinates are normalized
    gl_Position.w = 1.0;
    // Transforms by ModelView Matrix 
    gl_Position = gl_ModelViewProjectionMatrix * gl_Position;
    fragColor = vertexColor; 
}