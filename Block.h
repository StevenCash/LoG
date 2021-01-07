#ifndef BLOCK_H
#define BLOCK_H

#include "GLHeader.h"
#include <glm/gtc/matrix_transform.hpp> //glm::mat4 and more


class Block
{
 public:
  Block(const glm::mat4& projection,
	const float leftX,
	const float topY,
	const float rightX,
	const float botY,
	const unsigned char r,const unsigned char g, const unsigned char b,
	const unsigned int row);


  bool IsExtension(const int row) const ;
  void Extend();
  void Draw();
  void SetupGraphics();

  ~Block();


private:
  void SetupShader();
  
  const glm::mat4& m_projection;
  float m_leftX;
  float m_topY;
  float m_rightX;
  float m_botY;
  unsigned int m_row;
  
  GLuint m_shaderProgram;

  GLuint m_VBO;
  GLuint m_EBO;

  GLuint m_aPos;
  GLuint m_mvp;
  
};

#endif
