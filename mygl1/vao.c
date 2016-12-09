/* Create VAO, this includes creating vertices, VBO, EBO */

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

/* Create VAO, this includes creating vertices, VBO, EBO */
void createVAO(int  *pVAO, int  *pVBO, int  *pEBO){
    // Vertex data : 4 vertices for 2 triangles
    GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f,  // Top Right
         0.5f, -0.5f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f,  // Bottom Left
        -0.5f,  0.5f, 0.0f   // Top Left 
    };
    // Indices
    GLuint indices[]={
        0, 1, 3, // Triangle 1
        1, 2, 3  // Triangle 2
    };
    
    
    // VBO, VAO, EBO
    
    glGenVertexArrays(1, pVAO);
    glGenBuffers(1, pVBO);
    glGenBuffers(1, pEBO);
    
    // Bind VAO
    glBindVertexArray(*pVAO);
    
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, *pVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *pEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Some more settings
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    
    // Unbind VBO+VAO, but not EBO !!!
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
