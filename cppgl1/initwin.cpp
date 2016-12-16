/* By Oleksiy Grechnyev
 * Initialize GLFW and GLEW and create a window 
 * Also initialzies error callback (which must be early)
 * No need to use classes here as GLFW window id is self-contained
 * Also contains fatalError functions */ 
#include <iostream>
#include <cstdlib>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

namespace mygl{

    /* Error callback to log error messages */
    void errorCallback(int error, const char* description){
        printf("Goblin error : %s \n", description);
        using namespace std;
        cout << "Goblin error : " <<  description << endl;
    }

    // Print the error message and exit
    void fatalError(const char *text){
        using namespace std;
        cout << text << endl;
        glfwTerminate();
        exit(-1);
    }

    // The 2-string version
    void fatalError2(const char *text1, const char *text2){
        using namespace std;
        cout << text1 << text2 << endl;
        glfwTerminate();
        exit(-1);
    }

    //-----------------------------
    /* Initialize GLFW and GLEW and create a window
    Exits with an error message if an error */
    GLFWwindow *initWindow(int width, int height, const char* windowTitle){
        // Init GLFW
        
        glfwInit();
        // Error callback should be set early
        glfwSetErrorCallback(errorCallback);
        
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

}