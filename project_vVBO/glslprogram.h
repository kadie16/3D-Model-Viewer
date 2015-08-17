#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H
#include <string>
#include <gl.h>
#include <fstream>
#include <vector>
#include "errors.h"

class GLSLProgram
{
public:
    GLSLProgram();
    void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
    void linkShaders();
    void addAttribute(const std::string& attribName);
    void use();
    void unuse();
private:
    int _numAttributes;
    void compileShader(const std::string &filePath, GLuint id);
    GLuint _programID;
    GLuint _vertexShaderID;
    GLuint _fragmentShaderID;
};

#endif // GLSLPROGRAM_H
