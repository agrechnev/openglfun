/* Create VAO, this includes creating vertices, VBO, EBO */

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "initwin.h"

/* Create VAO, this includes creating vertices, VBO, EBO 
    pVAO, pVBO, pEBO = pointers to VAO, VBO, EBO
    vertices[], indices[]  = data arrays
     ver_size = sizeof(vertices)
     ind_size = sizeof(indices)
     ver_type = type of vertex data:
         1 = xyz
         2 = xyzrgb
*/
void createVAO(int  *pVAO, int  *pVBO, int  *pEBO, GLfloat* vertices, size_t  ver_size, GLuint* indices, size_t ind_size, int ver_type){
    
    // VBO, VAO
    
    glGenVertexArrays(1, pVAO);
    glGenBuffers(1, pVBO);
    
    // Bind VAO
    glBindVertexArray(*pVAO);
    
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, *pVBO);
    glBufferData(GL_ARRAY_BUFFER, ver_size, vertices, GL_STATIC_DRAW);
    
    // Create and bind EBO, ignore if pEBO==null
   if (pEBO!=NULL){
     glGenBuffers(1, pEBO);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *pEBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_size, indices, GL_STATIC_DRAW);
   }
    
    // Set up the arrays
    switch (ver_type){
      case 1:  // xyz 
         // xyz array (0)
         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid *)0);
         glEnableVertexAttribArray(0);
         break;

      case 2:  // xyzrgb
         // xyz array (0)
         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid *)0);
         glEnableVertexAttribArray(0);

         // rgb array (1)
         glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
         glEnableVertexAttribArray(1);

         break;

      default:
        fatalError("createVAO: wrong ver_type !");
   }
    
    // Unbind VBO+VAO, but not EBO !!!
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
