//
//  openGLWindow.cpp
//
//  Created by Kadie Jaffe on 6/24/15.
//
//

#include "openGLWindow.h" 

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
        fprintf( stderr, "GLFW initialization failed\n" );
        return -1;
    }

