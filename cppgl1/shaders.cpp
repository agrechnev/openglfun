/* Create shaders and shader program */

#include <stdio.h>
#include <stdlib.h>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>


// Local includes, needed for fataLError2()
#include "initwin.hpp"

/* Read a file as a single allocated string, returns NULL if error */
char *readFile(char * fileName){
    char *buffer; // The bufer to create
    size_t fileSize; // File size
    
    FILE* file= fopen(fileName, "r"); // Open file
    if (file==NULL) return NULL;
    
    // Determine size
    if (fseek(file, 0, SEEK_END)) return NULL;
    fileSize = ftell(file);
    if (fileSize <=0) return NULL;
    rewind(file);
    
    // Allocate memory and read
    buffer = (char *)malloc(fileSize+1);
    if (buffer==NULL) return NULL;
    
    // Read data to buffer
    fread (buffer, 1, fileSize, file);
    
    buffer[fileSize]='\0'; // End of C string
    
    fclose(file);
    
    return buffer;
}

/* Create shaders and the shader program from external files*/
GLuint createShaderProgram(char* vertexShaderFile,  char* fragmentShaderFile){
    
    using namespace mygl;
    
    // Read files
    char *vertexShaderSource=readFile(vertexShaderFile);
    if (vertexShaderSource==NULL) fatalError2("ERROR::SHADER:: Canntot read file ", vertexShaderFile);
    
    char *fragmentShaderSource=readFile(fragmentShaderFile);
    if (fragmentShaderSource==NULL) fatalError2("ERROR::SHADER:: Canntot read file ", fragmentShaderFile);
    
    // Build the shader program
    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const GLchar  * const *)&vertexShaderSource, NULL);
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
    glShaderSource(fragmentShader, 1, (const GLchar  * const *)&fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fatalError2("ERROR::SHADER:FRAGMENT::COMPILATION_FAILED\n", infoLog);
    }
    
    // Shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fatalError2("ERROR::SHADER::PROGRAM::LINKING_FAILED\n", infoLog);
    }
    
    // Delete shaders: we don't need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return shaderProgram;
}
