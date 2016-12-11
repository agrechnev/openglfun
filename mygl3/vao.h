/* Create VAO, this includes creating vertices, VBO, EBO */
#ifndef VAO_H_
#define VAO_H_
 
/* Create VAO, this includes creating vertices, VBO, EBO 
    pVAO, pVBO, pEBO = pointers to VAO, VBO, EBO
    vertices[], indices[]  = data arrays
     ver_size = sizeof(vertices)
     ind_size = sizeof(indices)
     ver_type = type of vertex data:
         1 = xyz
         2 = xyzrgb
*/
void createVAO(int  *pVAO, int  *pVBO, int  *pEBO, GLfloat* vertices, size_t  ver_size, GLuint* indices, size_t ind_size, int ver_type);

#endif
