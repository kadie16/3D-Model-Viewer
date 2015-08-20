#version 120
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 3 floats
attribute vec3 vertexPosition;
uniform vec3 vertexColor; 
varying vec4 fragColor;

//neHE
varying vec3 normal;
varying vec3 vertex_to_light_vector;

void main() {
    //Set the x,y position on the screen

    gl_Position.xyz = vertexPosition;
    //Indicate that the coordinates are normalized
    gl_Position.w = 1.0;
    // Transforms by ModelView Matrix 
    gl_Position = gl_ModelViewProjectionMatrix * gl_Position;
    fragColor = vec4(vertexColor, 1.0f); 

    // Transforming The Normal To ModelView-Space
    normal = gl_NormalMatrix * gl_Normal;
 
    // Transforming The Vertex Position To ModelView-Space
    vec4 vertex_in_modelview_space = gl_ModelViewMatrix * vec4(vertexPosition, 1.0);
 
    // Calculating The Vector From The Vertex Position To The Light Position
    vertex_to_light_vector = vec3(gl_ModelViewMatrix * (-vertex_in_modelview_space));
}