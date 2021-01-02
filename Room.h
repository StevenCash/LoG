#ifndef ROOM_H
#define ROOM_H
//**********************************************
//Class for loading/displaying a room based on a bitmap


#include <glm/gtc/matrix_transform.hpp> //glm::mat4 and more
#include <string>
#include "GLHeader.h"
#include <vector>

class Block;

//Class
class Room
{
 public:
  Room(const glm::mat4& projection, const std::string& mapFileName);

  virtual ~Room();

  virtual void Draw();
 protected:
  //Disabled operations
  Room(const Room& room);
  Room operator=(const Room& room);

 private:
  //data members
  const glm::mat4& m_projection;

  std::vector<Block*> m_blocks;
  
  //TBD move to tile/whatever class
  GLuint m_locationMVP;


  GLuint m_VAO;
  GLuint m_VBO;
  
};

#endif //ROOM_H
