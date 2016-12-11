#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// GLEW
#define GLEW_STATIC
/** GL2 by Oleksiy Grechnyev 
 *  Display 2 triangles with OpenGL
*   Use two different shader programs (of 2 colors) and two different VAOs
 *  Background color changes to random RGB every time you press a key
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

    // Yellow
    GLchar* fragmentShaderSource1="#version 330 core\n"
   "out vec4 color;\n"
   "void main(){color=vec4(1.0f, 1.0f, 0.0f, 1.0f);}\n\0";

    GLuint shaderProgram1 =  createShaderProgram(fragmentShaderSource1);
    
   // Blue
    GLchar* fragmentShaderSource2="#version 330 core\n"
   "out vec4 color;\n"
   "void main(){color=vec4(0.0f, 0.0f, 1.0f, 1.0f);}\n\0";

    GLuint shaderProgram2 =  createShaderProgram(fragmentShaderSource2);

    //----
    // Vertex data, VBO, VAO
   // Vertex data : 2 triangles for 2 different VAOs
    GLfloat vertices1[] = {
         -0.8f,  -0.3f, 0.0f,  // Triangle 1
         -0.2f,  -0.3f, 0.0f,  
         -0.5f,   0.3f, 0.0f 
    };
    // Indices
    GLuint indices1[]={
        0, 1, 2  // Triangle 
    };

    GLfloat vertices2[] = {
          0.8f,  -0.3f, 0.0f,  // Triangle 2
          0.2f,  -0.3f, 0.0f,  
          0.5f,   0.3f, 0.0f 
    };
    // Indices
    GLuint indices2[]={
        0, 1, 2  // Triangle 
    };

    GLuint VAO1, VBO1, EBO1;
    createVAO(&VAO1, &VBO1, &EBO1, vertices1, sizeof(vertices1), indices1, sizeof(indices1));    

    GLuint VAO2, VBO2, EBO2;
    createVAO(&VAO2, &VBO2, &EBO2, vertices2, sizeof(vertices2), indices2, sizeof(indices2));

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
        
        // Draw the triangle 1
        glUseProgram(shaderProgram1);

        glBindVertexArray(VAO1);    
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Draw the triangle 2
        glUseProgram(shaderProgram2);

        glBindVertexArray(VAO2);    
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);        
        
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


