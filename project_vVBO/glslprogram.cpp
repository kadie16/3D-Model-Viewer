#include "glslprogram.h"

GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
{

}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
    _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (_vertexShaderID == 0)
        fatalError("Failed to Create Vertex Shader");
    _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (_vertexShaderID == 0)
        fatalError("Failed to Create Fragment Shader");
    compileShader(vertexShaderFilePath, _vertexShaderID);
    compileShader(fragmentShaderFilePath, _fragmentShaderID);

}

void GLSLProgram::compileShader(const std::string& filePath, GLuint id) {
    _programID = glCreateProgram();
    std::ifstream vertexFile(filePath.c_str());
    if (vertexFile.fail())
        fatalError("Failed to open " + filePath);
    std::string fileContents = "";
    std::string line;
    while (std::getline(vertexFile, line)) {
        fileContents += line + "\n";
    }
    vertexFile.close();
    const char* contentsPtr = fileContents.c_str();
    glShaderSource(id, 1, &contentsPtr, NULL);
    glCompileShader(id);
    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
        glDeleteShader(id);
        std::printf("%s\n", &(errorLog[0]));
        fatalError("Shader " + filePath + " failed to compile");
        return;
    }
}

void GLSLProgram::linkShaders() {
    glAttachShader(_programID, _vertexShaderID);
    glAttachShader(_programID, _fragmentShaderID);
    glLinkProgram(_programID);

    GLint isLinked = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> infoLog(maxLength);
        glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);
        glDeleteProgram(_programID);
        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);
        std::printf("%s\n", &(infoLog[0]));
        fatalError("Shaders failed to link");
    }
    glDetachShader(_programID, _vertexShaderID);
    glDetachShader(_programID, _fragmentShaderID);
    glDeleteShader(_vertexShaderID);
    glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::addAttribute(const std::string& attribName){
    glBindAttribLocation(_programID, _numAttributes++, attribName.c_str());
}

void GLSLProgram::use(){
    glUseProgram(_programID);
    for (int i = 0; i < _numAttributes; i++) {
        glEnableVertexAttribArray(i);
    }
}

void GLSLProgram::unuse(){
    glUseProgram(0);
    for (int i = 0; i < _numAttributes; i++) {
        glDisableVertexAttribArray(i);
    }
}

GLuint GLSLProgram::getUniformLocation(const std::string& uniformName){
   GLuint location = glGetUniformLocation(_programID, uniformName.c_str());
   if (location == GL_INVALID_VALUE) {
       fatalError("Uniform " + uniformName + " not found in shader");
   }
   return location;
}

