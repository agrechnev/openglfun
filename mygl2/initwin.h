#ifndef INITWIN_H_
#define INITWIN_H_
 
// Print error message and exit
void fatalError(char *text);

// The 2-string version
void fatalError2(char *text1, char *text2);

/* Initialize GLFW and GLEW and create a window
   Exits with an error message if an error */
GLFWwindow *initWindow(int width, int height, char* windowTitle);

#endif
