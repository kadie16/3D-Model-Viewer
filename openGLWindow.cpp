//  openGLWindow.cpp
//
//  Created by Kadie Jaffe on 6/24/15.
//
//

#include "openGLWindow.h" // header 

//include standard headers:
#include <stdio.h>
#include <stdlib.h>

//include glew (always include it first...magic)
#include <GL/glew.h>

//include glfw3 (handles window and keyboard)
#include <glfw3.h>
GLFWwindow* window;

// 3D math lib. Can write own, but GLM is handy
#include <glm/glm.hpp>
using namespace glm; // allows you to write vec3 instead of glm::vec3

// must have main function so compiler doesn't yell
int main( void )
{
    // First: Initialize GLFW
    if ( !glfwInit() )
    {
        cout << "GLFW initialization failed"; // should print output on screen 
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); //4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); // OpenGL version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Mac OS
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want old OpenGL?

    // Open a window and create the window's OpenGL context 
    GLFWwindow* window; 
    window = glfwCreateWindow(1024, 768, "Window Creation 1", NULL, NULL);
    if (window == NULL){
    	cout << "Failed to open GLFW window"
    }


