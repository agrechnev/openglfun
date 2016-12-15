/* Create VAO, this includes creating vertices, VBO, EBO */
#ifndef VAO_H_
#define VAO_H_

// Type of vertex data (ver_type)
// XYZ coords only
#define VAO_XYZ 1  
// XYZ coolrds + RGB color
#define VAO_XYZRGB 2
// XYZ coolrds + RGB color + ST texture coords
#define VAO_XYZRGBST 3

/* Create VAO, this includes creating vertices, VBO, EBO 
    pVAO, pVBO, pEBO = pointers to VAO, VBO, EBO
    vertices[], indices[]  = data arrays
     ver_size = sizeof(vertices)
     ind_size = sizeof(indices)
     ver_type = type of vertex data, e.g. VAO_XYZRBST
*/
void createVAO(GLuint *pVAO, GLuint *pVBO, GLuint *pEBO, GLfloat* vertices, size_t  ver_size, GLuint* indices, size_t ind_size, int ver_type);

/* Delete VAO, VBO and EBO 
   EBO is skipped if pEBO==NULL */
void deleteVAO(GLuint *pVAO, GLuint *pVBO, GLuint *pEBO);

#endif
