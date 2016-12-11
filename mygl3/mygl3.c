#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "math.h"

// GLEW
#define GLEW_STATIC
/** GL3 by Oleksiy Grechnyev 
 *  Fun with shaders 
 *  Triangle 1 uses time-dependent color via uniform
 *  Triangle 2 uses xyzrgb vertices and interpolated color, it moves
*
 *  This is based on the learnopengl.com tutorial
 *  But write everything by hand, using C (and not C++) and more modular structure
 */

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>


// Local includes
#include "initwin.h"
#include "shaders.h"
#include "vao.h"

//-------------------------------------------------------------------------------------------
// GLOBAL DATA


//-------------------------------------------------------------------------------------------
// Function prototypes

// Callbacks
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


// Other
float randf();

//-------------------------------------------------------------------------------------------
int main(){
    printf("Goblins WON !!!\n");
    
    // Seed random number generator
    srand(time(NULL));
    
    // Initialzie GLFW+GLEW, create window and viewport
    GLFWwindow* window = initWindow(800, 600, "Goblin OpenGL");
        
    // Set the callback functions    
    // Keyboard
    glfwSetKeyCallback(window, key_callback);
    
    //----
    // Create shaders and the shader program

    // Triangle 1: changes color
    //Vertex shader 1
    const GLchar* vertexShaderSource1="#version 330 core\n"
   "layout (location=0) in vec3 pos;\n"
   "void main(){\n"
   "gl_Position=vec4(pos, 1.0);\n"
   "}\n\0";

    // Fragment shader 1
    const GLchar* fragmentShaderSource1="#version 330 core\n"
   "uniform vec4 vertexColor;"
   "out vec4 color;\n"
   "void main(){\n"
   "color=vertexColor;\n"
   "}\n\0";

    GLuint shaderProgram1 =  createShaderProgram(vertexShaderSource1, fragmentShaderSource1);
    GLuint vertexColorLocation1 = glGetUniformLocation(shaderProgram1, "vertexColor");


    // Triangle 2: xyzrgb vertices
    //Vertex shader 2
    const GLchar* vertexShaderSource2="#version 330 core\n"
   "layout (location=0) in vec3 pos;\n"
   "layout (location=1) in vec3 color;\n"
   "uniform float xOffset;\n"
   "uniform float yOffset;\n"
   "out vec3 ourColor;\n"
   "void main(){\n"
   "gl_Position=vec4(pos.x+xOffset, -pos.y+yOffset, pos.z, 1.0);\n"
   "ourColor=color;\n"
   "}\n\0";

    // Fragment shader 2
    const GLchar* fragmentShaderSource2="#version 330 core\n"
   "in vec3 ourColor;"
   "out vec4 color;\n"
   "void main(){\n"
   "color=vec4(ourColor,1.0f);\n"
   "}\n\0";

    GLuint shaderProgram2 =  createShaderProgram(vertexShaderSource2, fragmentShaderSource2);
    GLuint xOffsetLocation2 = glGetUniformLocation(shaderProgram2, "xOffset");
    GLuint yOffsetLocation2 = glGetUniformLocation(shaderProgram2, "yOffset");

    //----
    // Vertex data, VBO, VAO
 

    // Triangle 1: changes color
    GLfloat vertices1[] = {
         -0.2f,  -0.3f, 0.0f,  
         -0.8f,  -0.3f, 0.0f,  
         -0.5f,   0.3f, 0.0f 
    };
    // Indices
    GLuint indices1[]={
        0, 1, 2  // Triangle 
    };

    GLuint VAO1, VBO1, EBO1;
    createVAO(&VAO1, &VBO1, &EBO1, vertices1, sizeof(vertices1), indices1, sizeof(indices1),1);    

    // Triangle 2 :xyzrgb verices


    GLfloat vertices2[] = {
          0.2f,  -0.3f, 0.0f,  1.0f, 0.0f, 0.0f,
          0.8f,  -0.3f, 0.0f,  0.0f, 1.0f, 0.0f,
          0.5f,   0.3f, 0.0f,  0.0f, 0.0f, 1.0f
    };
    // Indices
    GLuint indices2[]={
        0, 1, 2  // Triangle 
    };

    GLuint VAO2, VBO2, EBO2;
    createVAO(&VAO2, &VBO2, &EBO2, vertices2, sizeof(vertices2), indices2, sizeof(indices2),2);    

    //----
    // Set Clear (background) color
    glClearColor(randf(), randf(), randf(), 1.0f);
    
    // Uncomment this for wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // The game loop
    while (!glfwWindowShouldClose(window)){
        // Event handlers
        // This is where callback functions are called
        // Also allows to close the window normally without kill
        glfwPollEvents(); 
        
        // Rendering of each frame is done here
        // For now: clear the screen with a chosen clear (background) color
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw the triangles

        // Triangle 1 
        // Set the color
        GLfloat timeVal=(GLfloat)glfwGetTime();
        GLfloat redVal=(sin(timeVal*sqrt(2.0f))/2)+0.5f;
        GLfloat greenVal=(sin(timeVal)/2)+0.5f;
        GLfloat blueVal=(sin(timeVal*sqrt(3.0f))/2)+0.5f;
        glUseProgram(shaderProgram1);
        glUniform4f(vertexColorLocation1, redVal, greenVal, blueVal, 1.0f);
        

        glBindVertexArray(VAO1);    
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

 
        // Triangle 2
        glUseProgram(shaderProgram2);
        glUniform1f(xOffsetLocation2, sin(timeVal*sqrt(5.0f))*0.1f);
        glUniform1f(yOffsetLocation2, sin(timeVal*sqrt(5.5f))*0.1f);

        glBindVertexArray(VAO2);    
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); 
        
        glBindVertexArray(0);
        
        // Swap the buffers
        // This actually paints things in your window
        // If nothing else is implemented,
        // It paints a black window instead of empty frame
        glfwSwapBuffers(window);
    }
    // Free memory
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteBuffers(1, &EBO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    glDeleteBuffers(1, &EBO2);
    
    // Finish the program
    glfwTerminate();
    return 0;
} 
//-------------------------------------------------------------------------
//Callback functions

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    if (action==GLFW_PRESS) {
        printf("Press : %d\n", key);
        
        // Set random Clear color
        glClearColor(randf(), randf(), randf(), 1.0f);        
        
    } else if (action==GLFW_RELEASE)
        printf("Release : %d\n", key); 
        
    if (key==GLFW_KEY_ESCAPE && action==GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    
}



// Other functions
// Type float random number between 0.0f and 0.1f
float randf(){
    return (float)rand()/(float)RAND_MAX;
}


