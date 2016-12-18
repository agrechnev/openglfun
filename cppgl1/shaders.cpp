/**
 * By Oleksiy Grechnyev
 *
 * Class ShaderProg :
 * Create shaders and the shader program from external files
 */

#include <string>
#include <fstream>
#include <sstream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>


// Local includes, needed for fataLError2()
#include "initwin.hpp"

// The class
#include "shaders.hpp"

namespace mygl{
 // Read a file as a string, fatalError if exception
 std::string ShaderProg::readFile(const char * fileName){
   using namespace std;
    
   ifstream file;
   // Set up exceptions
   file.exceptions(ifstream::badbit);
    
   // Open and read file within the try block
   try{
     file.open(fileName);  // Open file
     stringstream fileStream; // The file as a stream

     // Read file into fileStream
     fileStream << file.rdbuf();

     file.close(); // Close file

     return fileStream.str();

   } catch (ifstream::failure e) {
     fatalError2("Cannot read file ", fileName);
   }
 }

 // Constructor
 ShaderProg::ShaderProg(const char *vertexPath, const char *shaderPath) {
   using namespace std;
   
   // Read the files as strings 
   string vertexShaderStr = readFile(vertexPath);
   string fragmentShaderStr = readFile(shaderPath);
   const char * vertexShaderSource = vertexShaderStr.c_str();
   const char * fragmentShaderSource = fragmentShaderStr.c_str();

    // Build the shader program
    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Check for errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fatalError2("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
    }
    
    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fatalError2("ERROR::SHADER:FRAGMENT::COMPILATION_FAILED\n", infoLog);
    }
    
    // Shader program
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    // Check for errors
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        fatalError2("ERROR::SHADER::PROGRAM::LINKING_FAILED\n", infoLog);
    }
    
    // Delete shaders: we don't need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
 }

 // Use program
 void ShaderProg::use(){
   glUseProgram(program);
 }

 // Getter
 GLuint ShaderProg::getProgram() {
    return program;
 }

}



