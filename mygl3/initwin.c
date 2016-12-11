/* Initialize GLFW and GLEW and create a window 
 Also initialzies error callback (which must be early)
 Also contains fatalError functions */ 
#include <stdio.h>
#include <stdlib.h>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

/* Error callback to log error messages */
void error_callback(int error, const char* description){
    printf("Goblin error : %s \n", description);
}

// Print the error message and exit
void fatalError(char *text){
    puts(text);
    glfwTerminate();
    exit(-1);
}

// The 2-string version
void fatalError2(char *text1, char *text2){
    printf("%s",text1);
    puts(text2);
    glfwTerminate();
    exit(-1);
}

//-----------------------------
/* Initialize GLFW and GLEW and create a window
   Exits with an error message if an error */
GLFWwindow *initWindow(int width, int height, char* windowTitle){
    // Init GLFW
    
    glfwInit();
    // Error callback should be set early
    glfwSetErrorCallback(error_callback);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Create the window
    GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);
    
    // Note: such error checks are VITAL
    // Segmentation fault otherwise
    if (window==NULL)  fatalError("Failed to open GLFW window !");
    
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if  (glewInit() != GLEW_OK)  fatalError("Failed to initialize GLEW !");
    
    // Set viewport
    // This is the point where a window actually appears on your screen
    // This is also the first time an OpenGL function (as opposed to GLFW and GLEW) is invoked
    int fbwidth, fbheight; // Viewport size
    glfwGetFramebufferSize(window, &fbwidth, &fbheight); // Get from window
    glViewport(0, 0, width, height);
    
    return window;
}

