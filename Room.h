#ifndef ROOM_H
#define ROOM_H
//**********************************************
//Class for loading/displaying a room based on a bitmap


#include <glm/gtc/matrix_transform.hpp> //glm::mat4 and more
#include <string>
#include "GLHeader.h"
#include <map>

class b2World;

//TBD instantiate the block map(s) in the class that creates rooms and pass them in
class Block;
class BlockMapKey;

//Class
class Room
{
 public:
  Room(b2World& physicsWorld,
       const glm::mat4& projection,
       const std::string& mapFileName);

  virtual ~Room();

  virtual void Draw();
 protected:
  //Disabled operations
  Room(const Room& room);
  Room operator=(const Room& room);

 private:
  //data members
  b2World& m_physicsWorld;
  const glm::mat4& m_projection;

  typedef std::map<BlockMapKey, Block*> BlockMap ;
  BlockMap m_blockMap; 


  void AddBlock(const BlockMapKey& blockMapkey,
		const int leftX,
		const int topY,
		const int rightX,
		const int botY,
		const unsigned int blockIndex);

  void HandleBlockCreation(int xStart,
			   int xEnd,
			   unsigned int blockIndex,
			   const int j);

};

#endif //ROOM_H
