/** By Oleksiy Grechnyev
 *  class VaoUnit
 *  This class includes VAO, VBO and (optionally EBO)
 *  It creates all respective buffers and such
 */
#ifndef VAO_HPP_
#define VAO_HPP_

// Type of vertex data 
typedef enum VertexType {XYZ, XYZ_RGB, XYZ_RGB_ST} VertexType;


namespace mygl{
 class VaoUnit{
     bool useEbo; // Is Ebo used or not?
     VertexType vertexDataType; // Type of vertex data, see above
     GLuint VAO, VBO, EBO; // The IDs of the respective objects
     
 public:
     
     
     /** Constructor: create a new VaoUnit
      *  vertices[], indices[]  = data arrays
      * verSize = sizeof(vertices)
      * indSize = sizeof(indices)
      * vertexType = type of vertex data
      * 
      * Note: if indices == nullptr, then EBO is ignored
      */
     VaoUnit(GLfloat* vertices, size_t  verSize, GLuint* indices, size_t indSize, VertexType vertexType);
     
     /* Destructor */
     ~VaoUnit();
     
     /* Bind this VAO object */
     void bind();

     /* Draw this VAO object (assuming triangles) */
     void draw(int n);
 };
}
#endif
