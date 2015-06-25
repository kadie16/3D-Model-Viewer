//  openGLWindow.cpp
//
//  Created by Kadie Jaffe on 6/24/15.
//
//

//#include "openGLWindow.h" // header

//include standard headers:
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
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
        std::cout << "GLFW initialization failed"; // should print output on screen
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); //4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); // OpenGL version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Mac OS
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want old OpenGL?
    
    // Open a window and create the window's OpenGL context
    window = glfwCreateWindow(1024, 768, "Window Creation 1", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to open GLFW window";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW\n";
        return -1;
    }

// Make Sure Can Capture Escape Key Press
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Background
    glClearColor(153.0f, 0.0f, 76.0f, 0.0f);

    do {
        // not drawing anything yet
        // Swap Buffers (??)
        //
        glfwSwapBuffers(window);
        glfwPollEvents();
        }  // Check if ESC key pressed or window closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
    
    // close window and terminate GLFW
    glfwTerminate();
    return 0;
}



