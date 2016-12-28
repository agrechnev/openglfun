/** CPPGL6 by Oleksiy Grechnyev 
 *
 * Same as 5, but using camera class from the tutorial
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

#include "camera.h"



//-------------------------------------------------------------------------------------------
// GLOBAL DATA

namespace mygl{
    
 // Global data   
 
 // Keyboard vars
 bool keys[1024]; // true = key pressed

 // Camera
 Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); // Global var using defaults
 // Mouse vars
 GLfloat lastX, lastY; // Last mouse position
 bool firstMouse=true; // true on the 1st iteration only

 // delta Time
 GLfloat deltaTime=0.0f;
 //-------------------------------------------------------------------------------------------
 // Function prototypes

 // Callbacks
 void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
 void mouseCallback(GLFWwindow* window, double xpos, double ypos);
 void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

 // Other
 // Calculate camera front from yaw & pitch
 void calcFront();

 // Do the actual movement
 void doMovement();
 
 // float random number between 0 and 1
 float randf();
 
 // Random unit 3-vector
 glm::vec3 randUV3();
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
    const GLuint SCREEN_WIDTH = 1200;
    const GLuint SCREEN_HEIGHT = 800;
    GLFWwindow* window = initWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Goblin OpenGL");
        
    // Set the callback functions    
    // Keyboard
    glfwSetKeyCallback(window, keyCallback);
    // Mouse
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    // Options
    glEnable(GL_DEPTH_TEST); // Needed for proper 3D
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Disable mouse cursor
    
    //----
    // Create shaders and the shader program

    // Load shaders
    ShaderProg shaderProgram1("shader_files/s1.vs", "shader_files/s1.frag");
    
    // Positions of 10 cubes
   glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
   };

    
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

    //--------
    // Cube rotation axes and velocities: randomize them !
    glm::vec3 cubeAxes[10];
    float cubeAV[10]; // Angular velocities
    // Loop over 10 cubes
    for (int cube=0; cube<10; cube++) {
        cubeAV[cube] = 4*randf()-2; // Between -2 and 2 RADIAN / time unit
        cubeAxes[cube] = randUV3(); // Random unit vector
    }
    
    
    //----
    // Set Clear (background) color
    glClearColor(0.5f, 1.0f, 1.0f, 1.0f);
    
    // Uncomment this for wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    
     GLfloat lastFrame=0.0f; // Last frame for calculating deltaTime
    // The game loop
    while (!glfwWindowShouldClose(window)){
        GLfloat timeValue = glfwGetTime(); // Get time
        deltaTime = timeValue - lastFrame;
        lastFrame = timeValue;

        // Event handlers
        // This is where callback functions are called
        // Also allows to close the window normally without kill
        glfwPollEvents(); 
        doMovement();
        
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
        

        
        // Set up view and projection (CAMERA): same for all cubes
        // View 
        glm::mat4 view;
        view = camera.GetViewMatrix();
        glUniformMatrix4fv(shaderProgram1.loc("view"), 1, GL_FALSE, glm::value_ptr(view));
        
        // Projection
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(shaderProgram1.loc("projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Loop over 10 cubes
        for (int cube=0; cube<10; cube++) {

            // Set up the transformations  
            // Model
            glm::mat4 model;
            model = glm::translate(model, cubePositions[cube]);
            model = glm::rotate(model, timeValue*cubeAV[cube], cubeAxes[cube]);
            glUniformMatrix4fv(shaderProgram1.loc("model"), 1, GL_FALSE, glm::value_ptr(model));

            // The actual draw
            vaoUnit1->draw(36);
        }
        

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

 // Keyboard callback
 // Escape + press/release for all keys
 void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode){            

    if (action==GLFW_PRESS) {
      keys[key]=true;
    } else if (action==GLFW_RELEASE) {
      keys[key]=false;
    }
    
    // ESC = exit

    if (key==GLFW_KEY_ESCAPE && action==GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);    
 }
 

 // Mouse callback
 void mouseCallback(GLFWwindow* window, double xpos, double ypos){
  if (firstMouse) {
   lastX = xpos;
   lastY = ypos;
   firstMouse=false;
   return;
  }


  // Calculate offsets
  GLfloat xoffset = xpos-lastX;
  GLfloat yoffset = lastY - ypos;
  // Store positions as last
  lastX = xpos;
  lastY = ypos;

  // Scale offsets with mouse sensitivity
  GLfloat sensitivity = 0.05f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  // Update camera
  camera.ProcessMouseMovement(xoffset, yoffset);
 }
 
 // Mouse wheel (scroll) callback: update fov
 void scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
     camera.ProcessMouseScroll(yoffset);
}

 //--------------------------
 // Other functions

 // Do the actual movement
 void doMovement(){
    // WASD = move camera     
    if (keys[ GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);;
 }


 //float random number between 0.0f and 0.1f
 float randf(){
    return (float)rand()/(float)RAND_MAX;
 }
 
 // Random unit 3-vector with spherical distribution
 glm::vec3 randUV3(){
     float t = acos(2*randf()-1);
     float p=M_PI*2*randf();
     glm::vec3 result(sin(t)*cos(p), sin(t)*sin(p), cos(t));
     return result;
 }
 
 
} // namespace mygl
