/** CPPGL3 by Oleksiy Grechnyev 
 *
 *  Starting 3D with all the funny matrices
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
 GLfloat parGlobal1 = 0.5f; // Parameter control by keys

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
    const GLuint SCREEN_WIDTH = 800;
    const GLuint SCREEN_HEIGHT = 600;
    GLFWwindow* window = initWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Goblin OpenGL");
        
    // Set the callback functions    
    // Keyboard
    glfwSetKeyCallback(window, key_callback);

    // Options
    glEnable(GL_DEPTH_TEST);
    
    //----
    // Create shaders and the shader program

    // Load shaders
    ShaderProg shaderProgram1("shader_files/s1.vs", "shader_files/s1.frag");

    //----
    // Vertex data, VBO, VAO
 

    // Model 1: XYZ, ST data (ST = texture X, texture Y)
    GLfloat vertices1[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
/*
    // Indices
    GLuint indices1[]={
        0, 1, 2,  // Triangle 1
        2, 3, 0  // Triangle 2
    };
*/
    // Create Vao Unit (a C++ class, beautiful !!!)
//    VaoUnit *vaoUnit1=new VaoUnit(vertices1, sizeof(vertices1), indices1, sizeof(indices1), XYZ_ST);
    VaoUnit *vaoUnit1=new VaoUnit(vertices1, sizeof(vertices1), nullptr, 0, XYZ_ST);

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Draw 

        shaderProgram1.use();        // Use the Program
        
        // Textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1); 
        glUniform1i(shaderProgram1.loc("ourTexture1"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2); 
        glUniform1i(shaderProgram1.loc("ourTexture2"), 1);
        
        GLfloat timeValue = glfwGetTime(); // Get time


        // Set up the transformations 
        // Model
        glm::mat4 model;
        model = glm::rotate(model, -timeValue*glm::radians(55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        // View
        glm::mat4 view;
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -(parGlobal1*5 + 1.0f)) );
        // Projection
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);;
        

        // Pass the transformations as uniforms
        glUniformMatrix4fv(shaderProgram1.loc("model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(shaderProgram1.loc("view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(shaderProgram1.loc("projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // The actual draw
        vaoUnit1->draw(36);
        

        // Swap the buffers
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
        

    // Up and down keys control something (if needed) between 0 and 1
    if (key==GLFW_KEY_UP && action==GLFW_PRESS) {
      parGlobal1+=0.1f;
      if (parGlobal1 > 1.0f) parGlobal1 = 1.0f;
    }
    
    if (key==GLFW_KEY_DOWN && action==GLFW_PRESS) {
      parGlobal1-=0.1f;
      if (parGlobal1 < 0.0f) parGlobal1 = 0.0f;
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
