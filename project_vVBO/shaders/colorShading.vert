#version 120
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats
attribute vec2 vertexPosition;

void main() {
    //Set the x,y position on the screen
    gl_Position.xy = vertexPosition;
    //the z position is zero since we are in 2D
    gl_Position.z = 0.0;
    
    //Indicate that the coordinates are normalized
    gl_Position.w = 1.0;
}