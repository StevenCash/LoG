#ifndef PORTAL_H
#define PORTAL_H

#include "Block.h"
#include "GLHeader.h"
#include <glm/gtc/matrix_transform.hpp> //glm::mat4 and more


class b2World;
class b2Body;

class Portal : public Block
{
  const char *vertexShaderSource;
  const char *fragmentShaderSource;
 public:
  Portal(b2World& physicsWorld,
	const glm::mat4& projection,
	const int leftX,
	const int topY,
	const int rightX,
	const int botY,
	const unsigned blockIndex);

  /*
  bool IsExtension(const int row) const ;
  void Extend();
  void Draw();
  void SetupGraphics();
  void SetupPhysicsInfo();
  */
  
  virtual ~Portal();


private:
};

#endif
