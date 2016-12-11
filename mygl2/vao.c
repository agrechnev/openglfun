/* Create VAO, this includes creating vertices, VBO, EBO */

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

/* Create VAO, this includes creating vertices, VBO, EBO */
void createVAO(int  *pVAO, int  *pVBO, int  *pEBO, GLfloat* vertices, size_t  ver_size, GLuint* indices, size_t ind_size){
    
    // VBO, VAO, EBO
    
    glGenVertexArrays(1, pVAO);
    glGenBuffers(1, pVBO);
    glGenBuffers(1, pEBO);
    
    // Bind VAO
    glBindVertexArray(*pVAO);
    
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, *pVBO);
    glBufferData(GL_ARRAY_BUFFER, ver_size, vertices, GL_STATIC_DRAW);
    
    // Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *pEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_size, indices, GL_STATIC_DRAW);
    
    // Some more settings
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    
    // Unbind VBO+VAO, but not EBO !!!
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
