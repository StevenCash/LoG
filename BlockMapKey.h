#ifndef BLOCKMAPKEY_H
#define BLOCKMAPKEY_H

class BlockMapKey
{
public:
  BlockMapKey(const int leftX, const int rightX,
	      unsigned int index);
  
  bool operator<(const BlockMapKey& right) const;
private:
  const int m_leftX;
  const int m_rightX;
  const int m_index;
};

#endif
