/**
 * By Oleksiy Grechnyev
 *
 * Class ShaderProg :
 * Create shaders and the shader program from external files
 */

#include <string>

#ifndef SHADERS_HPP_
#define SHADERS_HPP_
 
namespace mygl{


 class ShaderProg{
   GLuint program; // The program ID after it's compiled successfully

   // Read a file as a string, fatalError if exception
   std::string readFile(const char * fileName);

  public:
  // Constructor
  ShaderProg(const char *vertexPath, const char *shaderPath);

  // Use program
  void use();

  // Getter
  GLuint getProgram();
 };

 
}

#endif
