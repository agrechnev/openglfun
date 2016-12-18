/** CPPGL1 by Oleksiy Grechnyev 
 *  More fun with textures: 2 textures, mixing
 * 
 *  This is based on the learnopengl.com tutorial
 *  But write everything by hand, using C (and not C++) and more modular structure
 */

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

// GLEW
#define GLEW_STATIC


#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>


// Local includes
#include "initwin.hpp"
#include "shaders.hpp"
#include "vao.hpp"
#include "texture.hpp"



//-------------------------------------------------------------------------------------------
// GLOBAL DATA

namespace mygl{
 GLfloat mixingGlobal = 0.5f; // Mixing parameter

 //-------------------------------------------------------------------------------------------
 // Function prototypes

 // Callbacks
 void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

 // Other
 float randf();
}

//-------------------------------------------------------------------------------------------
// MAIN
//-------------------------------------------------------------------------------------------
int main(){
    using namespace mygl;
    using namespace std;

    cout << "Goblins WON !!!" << endl;
    
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
    ShaderProg shaderProgram1("shader_files/s1.vs", "shader_files/s1.frag");
    GLuint vertexColorLocation1 = glGetUniformLocation(shaderProgram1.getProgram(), "vertexColor");

    //----
    // Vertex data, VBO, VAO
 

    // Triangle 1: XYZ, RGB, ST data (ST = texture X, texture Y)
    GLfloat vertices1[] = {
        //        XYZ                    RGB                 ST
         -0.5f,  -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
         -0.5f,   0.5f, 0.0f,     0.0f, 1.0f, 0.0f,      0.0f, 1.0f,
          0.5f,   0.5f, 0.0f,     0.0f, 0.0f, 1.0f,      1.0f, 1.0f,
          0.5f,  -0.5f, 0.0f,     1.0f, 1.0f, 0.0f,      1.0f, 0.0f
    };
    // Indices
    GLuint indices1[]={
        0, 1, 2,  // Triangle 1
        2, 3, 0  // Triangle 2
    };

    // Create Vao Unit (a C++ class, beautiful !!!)
    VaoUnit *vaoUnit1=new VaoUnit(vertices1, sizeof(vertices1), indices1, sizeof(indices1), XYZ_RGB_ST);

    //-----
    // Create textures
    GLuint texture1 = createTexture("../texture_global/container.jpg");
    GLuint texture2 = createTexture("../texture_global/awesomeface.png");    

    //----
    // Set Clear (background) color
    glClearColor(0.5f, 1.0f, 1.0f, 1.0f);
    
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

        shaderProgram1.use();        // Use the Program
        
        // Textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1); 
        glUniform1i(glGetUniformLocation(shaderProgram1.getProgram(), "ourTexture1"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2); 
        glUniform1i(glGetUniformLocation(shaderProgram1.getProgram(), "ourTexture2"), 1);
        
        GLfloat timeValue = glfwGetTime(); // Get time

        // Time-based mixing
        glUniform1f(glGetUniformLocation(shaderProgram1.getProgram(), "mixing"), (1+sin(timeValue))*0.5 );

        // Keyboard-based mixing
        // glUniform1f(glGetUniformLocation(shaderProgram1.getProgram(), "mixing"), mixingGlobal );

        vaoUnit1->bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
        
        // Swap the buffers
        // This actually paints things in your window
        // If nothing else is implemented,
        // It paints a black window instead of empty frame
        glfwSwapBuffers(window);
    }
    // Free memory
    delete vaoUnit1;
    
    // Finish the program
    glfwTerminate();
    return 0;
} 

namespace mygl{
 //-------------------------------------------------------------------------
 //Callback functions

 // Escape only, no funny stuff
 void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
        

    // Up and down keys control the mixing
    if (key==GLFW_KEY_UP && action==GLFW_PRESS) {
      mixingGlobal+=0.1f;
      if (mixingGlobal > 1.0f) mixingGlobal = 1.0f;
    }
    
    if (key==GLFW_KEY_DOWN && action==GLFW_PRESS) {
      mixingGlobal-=0.1f;
      if (mixingGlobal < 0.0f) mixingGlobal = 0.0f;
    }

    if (key==GLFW_KEY_ESCAPE && action==GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);    
 }


 // Other functions
 // Type float random number between 0.0f and 0.1f
 float randf(){
    return (float)rand()/(float)RAND_MAX;
 }
 
} // namespace mygl
