/** By Oleksiy Grechnyev
 *  class VaoUnit
 *  This class includes VAO, VBO and (optionally EBO)
 *  It creates all respective buffers and such
 */

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "initwin.hpp"

#include "vao.hpp"

namespace mygl{
    
      /** Constructor: create a new VaoUnit
      *  vertices[], indices[]  = data arrays
      * verSize = sizeof(vertices)
      * indSize = sizeof(indices)
      * vertexType = type of vertex data
      * 
      * Note: if indices == nullptr, then EBO is ignored
      */
  VaoUnit::VaoUnit(GLfloat* vertices, size_t  verSize, GLuint* indices, size_t indSize, VertexType vertexType){
    // Set up parameters
    if (indices==nullptr)  {
        useEbo=false;
    } else {
        useEbo=true;
    }
    vertexDataType = vertexType;
      
    // Create VBO, VAO
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // Bind VAO
    glBindVertexArray(VAO);
    
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verSize, vertices, GL_STATIC_DRAW);
    
    // Create and bind EBO if needed
   if (useEbo){
     glGenBuffers(1, &EBO);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, indices, GL_STATIC_DRAW);
   }
    
    // Set up the arrays
    switch (vertexDataType){
      case XYZ:  // xyz 
         // xyz array (0)
         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid *)0);
         glEnableVertexAttribArray(0);
         break;

      case XYZ_RGB:  // xyzrgb
         // xyz array (0)
         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid *)0);
         glEnableVertexAttribArray(0);

         // rgb array (1)
         glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
         glEnableVertexAttribArray(1);

         break;

      case XYZ_RGB_ST:  // xyzrgbrs
         // xyz array (0)
         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid *)0);
         glEnableVertexAttribArray(0);

         // rgb array (1)
         glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
         glEnableVertexAttribArray(1);

         // st array (2) (texture coords)
         glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid *)(6*sizeof(GLfloat)));
         glEnableVertexAttribArray(2);
         
         break;
         
      default:
        fatalError("VaoUnit::VaoUnit wrong vertexType !");
   }
    
    // Unbind VBO+VAO, but not EBO !!!
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
 }

/* Destructor */
 VaoUnit:: ~VaoUnit(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    if (useEbo) glDeleteBuffers(1, &EBO);   
 }

  /* Bind this VAO object */
  void VaoUnit::bind(){
       glBindVertexArray(VAO);
  }

  /* Draw this VAO object (assuming triangles) */
  void VaoUnit::draw(int n){
      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, n, GL_UNSIGNED_INT, 0);
        
      glBindVertexArray(0);
  }
}