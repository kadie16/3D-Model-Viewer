#include "errors.h"
#include <iostream>
#include <gl.h>
void fatalError(std::string errorString)
{
    std::cout << "ERROR: " << errorString << std::endl;
    //std::cout << "Press any key to quit" << std::endl;
    //int temp;
   // std::cin >> temp;
    std::terminate();
}

int CheckGLErrors()
{
  int errCount = 0;
  for(GLenum currError = glGetError(); currError != GL_NO_ERROR; currError = glGetError())
  {
    //Do something with `currError`.
    std::cout << currError << ", " ;
    ++errCount;
  }
  std::cout << std::endl << errCount << " openGL errors in total";
  return errCount;
}
