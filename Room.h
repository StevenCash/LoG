#ifndef ROOM_H
#define ROOM_H
//**********************************************
//Class for loading/displaying a room based on a bitmap


#include <glm/gtc/matrix_transform.hpp> //glm::mat4 and more
#include <string>
#include "GLHeader.h"
#include <map>

//TBD instantiate the block map(s) in the class that creates rooms and pass them in
class Block;
class BlockMapKey;

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

  typedef std::map<BlockMapKey, Block*> BlockMap ;
  BlockMap m_blockMap; 


  void AddBlock(const BlockMapKey& blockMapkey,
		const float leftX,
		const float topY,
		const float rightX,
		const float botY,
		const unsigned char r, const unsigned char g, const unsigned char b,
		const unsigned int row);

};

#endif //ROOM_H
