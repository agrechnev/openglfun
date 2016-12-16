/**
 * texture.c : Create and bind texture from an image file
 * By Oleksiy Grechnyev
 */

#include <stdlib.h>

// GLEW
#define GLEW_STATIC


#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// SOIL
#include <SOIL/SOIL.h>

// Local includes
#include "initwin.hpp"


/* Create a texture object from an image file */
GLuint createTexture(char *fileName){
    using namespace mygl;
    
    // Create and bind texture objects
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // Set wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Set filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Load image from a jpg file with SOIL
    int image_width, image_height;
    unsigned char* image=SOIL_load_image(fileName,  &image_width, &image_height, 0, SOIL_LOAD_RGB);
    
    if (image==NULL) fatalError2("ERROR:: TEXTURE :: Cannot load image ", fileName);
    
    // Set up the image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // Free memomry and unbind
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return texture;
}