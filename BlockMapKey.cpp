#include "BlockMapKey.h"


BlockMapKey::BlockMapKey(int leftX, int rightX,
			 unsigned int index):
  m_leftX(leftX),
  m_rightX(rightX),
  m_index(index)
{
  
}

bool BlockMapKey::operator<(const BlockMapKey& right) const
{
  return m_index < right.m_index;
}
