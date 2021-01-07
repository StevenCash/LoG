#ifndef BLOCKMAPKEY_H
#define BLOCKMAPKEY_H

class BlockMapKey
{
public:
  BlockMapKey(const int leftX, const int rightX,
	      const unsigned char r,
	      const unsigned char g,
	      const unsigned char b);
  
  bool operator<(const BlockMapKey& right) const;
private:
  const int m_leftX;
  const int m_rightX;
  const unsigned char m_r;
  const unsigned char m_g;
  const unsigned char m_b;

  //what row was this created with?
  unsigned int m_row;
};

#endif
