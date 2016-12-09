/* Create shaders and shader program */

#include <stdio.h>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>


// Local includes, needed for fataLError2()
#include "initwin.h"

/* Create shaders and the shader program */
GLuint createShaderProgram(){
    // Shaders's sources as string literals
    const GLchar* vertexShaderSource="#version 330 core\n"
   "layout (location=0) in vec3 pos;\n"
   "void main(){gl_Position=vec4(pos.x, pos.y, pos.z, 1.0);}\n\0";
 
   const GLchar* fragmentShaderSource="#version 330 core\n"
   "out vec4 color;\n"
   "void main(){color=vec4(1.0f, 0.5f, 0.0f, 1.0f);}\n\0";
    
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
