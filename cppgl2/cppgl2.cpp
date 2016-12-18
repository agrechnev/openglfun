/** CPPGL2 by Oleksiy Grechnyev 
 *
 *  Fun with rotation + GLM matrices
 *  Uses 2 transformation (and 2 mixings) to 1 sets of data, FUN !
 * 
 *  This is loosely based on the learnopengl.com tutorial
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

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    GLuint vertexColorLocation1 = shaderProgram1.loc("vertexColor");

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
        glUniform1i(shaderProgram1.loc("ourTexture1"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2); 
        glUniform1i(shaderProgram1.loc("ourTexture2"), 1);
        
        GLfloat timeValue = glfwGetTime(); // Get time


        // Set up the transformation with GML (+mixing)
        float scl=(3+sin(timeValue*sqrt(2.0)))/8.0; // The scale from 0.25 to 0.5
        float angle=timeValue*sqrt(3.0); // Angle in radians for rotation
        
        float mixing1=(1+sin(timeValue))*0.5f;
        float mixing2=(1+sin(timeValue*sqrt(1.5)))*0.5f;

        glm::mat4 trans1; // trans1 is changing size      
        trans1 = glm::translate(trans1,  glm::vec3(0.5f, -0.5f, 0.0f));  
        trans1 = glm::scale(trans1, glm::vec3(scl, scl, scl));
 
        glm::mat4 trans2; // trans2 is spinning
        trans2 = glm::rotate(trans2, angle, glm::vec3(0.0f, 0.0f, 1.0f)); 
        trans2 = glm::translate(trans2,  glm::vec3(-0.5f, +0.5f, 0.0f));  
        trans2 = glm::scale(trans2, glm::vec3(0.5f, 0.5f, 0.5f));

        // Use 2 transformations to draw 2 objects from one set of data
        glUniformMatrix4fv(shaderProgram1.loc("transform"), 1, GL_FALSE, glm::value_ptr(trans1));
        glUniform1f(shaderProgram1.loc("mixing"), mixing1);
        vaoUnit1->draw(6);
        
        glUniformMatrix4fv(shaderProgram1.loc("transform"), 1, GL_FALSE, glm::value_ptr(trans2));
        glUniform1f(shaderProgram1.loc("mixing"), mixing2);
        vaoUnit1->draw(6);

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
