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
  if(m_leftX < right.m_leftX)
    {
      return true;
    }
  else if(m_leftX == right.m_leftX)
    {
      if(m_rightX < right.m_rightX)
        {
          return true;
        }
      else if (m_rightX == right.m_rightX)
        {
          if(m_index < right.m_index)
            {
              return true;
            }
	}
    }

  return false;

}
