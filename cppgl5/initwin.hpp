

#ifndef INITWIN_HPP_
#define INITWIN_HPP_
    
namespace mygl{    
    // Print error message and exit
    void fatalError(const char *text);

    // The 2-string version
    void fatalError2(const char *text1, const char *text2);

    /* Initialize GLFW and GLEW and create a window
    Exits with an error message if an error */
    GLFWwindow *initWindow(int width, int height, const char* windowTitle);
}
#endif
