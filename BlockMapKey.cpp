#include "BlockMapKey.h"



BlockMapKey::BlockMapKey(int leftX, int rightX,
			 unsigned char r,
			 unsigned char g,
			 unsigned char b):
  m_leftX(leftX),
  m_rightX(rightX),
  m_r(r),
  m_g(g),
  m_b(b)
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
	  if(m_r < right.m_r)
	    {
	      return true;
	    }
	  else if(m_r == right.m_r)
	    {
	      if(m_g < right.m_g)
		{
		  return true;
		}
	      else
		{
		  if(m_b < right.m_b)
		    {
		      return true;
		    }
		}
	    }
	}
    }

  return false;
}
