//https://youtu.be/N614k7LVuMU -wtf is this ?

#include "Room.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ShaderUtil.h"
#include "Block.h"
#include "BlockMapKey.h"

Room::Room(b2World& physicsWorld,
	   const glm::mat4& projection,
	   const std::string& mapFileName):
  m_physicsWorld(physicsWorld),
  m_projection(projection)
{
 
  /********************************************************/
  
  //Using SDL_Image to load the bmp into a SDL_Surface
  SDL_Surface* map_image_surface = IMG_Load(mapFileName.c_str());
  if (map_image_surface == NULL) {
    std::cerr << "IMG_Load: " << SDL_GetError() << std::endl;
    return;
  }

  SDL_LockSurface(map_image_surface);
  std::cout << (int)map_image_surface->format->BitsPerPixel << "   " << (int)map_image_surface->format->BytesPerPixel  << std::endl;
  std::cout << "Format enum: " <<  SDL_GetPixelFormatName(map_image_surface->format->format) << std::endl;
  if(map_image_surface->format->format != SDL_PIXELFORMAT_BGR24)
    {
      std::cerr << "Incorrect pixel format.  Need SDL_PIXELFORMAT_BGR24" << std::endl;
      return;
    }

  //Don't need this for the above pixel format
  /*
  SDL_Palette *pPalette = map_image_surface->format->palette;
  if(!pPalette)
    {
      std::cout << "Null palette" << std::endl;
    }
  */

  
  unsigned char* pixels = static_cast<unsigned char*>(map_image_surface->pixels);

  //get the red attribute of the first pixel in the row
  unsigned int lastIndex = (pixels[2] << 16) | (pixels[1] << 8) | (pixels[0]);
  int pixelRunCount = 0;
  int xStart=0;
  int pitch = map_image_surface->pitch;
  int pixelNum = 0;
  for(int j = 0; j < map_image_surface->h; ++j)
    {
      int offset = j * pitch; //offset into the byte array of pixels
      lastIndex = (pixels[offset+2] << 16) | (pixels[offset+1] << 8) | (pixels[offset+0]);
      pixelRunCount = 0;
      xStart = 0;
      for(int i = 0; i < pitch;)
	{
	  unsigned char b = pixels[offset + i++];
	  unsigned char g = pixels[offset + i++];
	  unsigned char r = pixels[offset + i++];
	  ++pixelNum;
	  unsigned int blockIndex = (r << 16) | (g << 8) | (b);
	  //Check to see if it's still the same texture
	  if(blockIndex!=lastIndex || pixelNum == map_image_surface->w) //we've reached the end.  create the block object that fits this count.
	    {
	      int xEnd = xStart + pixelRunCount;
	      //Block creation
	      if(lastIndex == 0x00FF0000) //Only create objects when the Red byte is 255 - TBD: Look up index to determine what to do
		{
		  HandleBlockCreation(xStart,xEnd,blockIndex,j);
		}
    
	      //reset
	      if(pixelNum == map_image_surface->w) //reset when we reach the end of the row
		{
		  xStart = 0;
		  pixelNum = 0;
		}
	      else //reset at the end of the run
		{
		  xStart += pixelRunCount;
		  lastIndex = blockIndex;
		}
	      pixelRunCount = 1;
	      
	    } // last in run or row
	  else
	    {
	      ++pixelRunCount;
	    }

	}
    }
  SDL_UnlockSurface(map_image_surface);    
  SDL_FreeSurface(map_image_surface);

  BlockMap::iterator iter = m_blockMap.begin();
  for(;iter != m_blockMap.end(); ++iter)
    {
      iter->second->SetupGraphics();
      iter->second->SetupPhysicsInfo();
    }

}

Room::~Room()
{
  BlockMap::const_iterator iter = m_blockMap.begin();
  for(;iter != m_blockMap.end(); ++iter)
    {
      delete  iter->second;
    }
}



void Room::Draw()
{
  BlockMap::const_iterator iter = m_blockMap.begin();
  for(;iter != m_blockMap.end(); ++iter)
    {
      iter->second->Draw();
    }
}

void Room::AddBlock(const BlockMapKey& blockMapKey,
		    const int leftX,
		    const int topY,
		    const int rightX,
		    const int botY,
		    const unsigned int blockIndex)
{
  Block * pBlock = new Block(m_physicsWorld,
			     m_projection,
			     leftX,
			     topY,
			     rightX,
			     botY,
			     blockIndex);

  m_blockMap[blockMapKey]= pBlock;
}

void Room::HandleBlockCreation(int xStart,
			       int xEnd,
			       unsigned int blockIndex,
			       const int j)
{
  {
    //make sure the block isn't already in the map
    BlockMapKey tempBlockMapKey(xStart, xEnd, blockIndex);
    
    BlockMap::iterator iter = m_blockMap.find(tempBlockMapKey);
    
    if(iter == m_blockMap.end())
      {
	AddBlock(tempBlockMapKey,
		 xStart,
		 j,
		 xEnd,
		 j+1,
		 blockIndex);
      }
    else
      {
	//check to see if an existing block just needs to be stretched downward
	Block *pBlock = iter->second;
	if(pBlock->IsExtension(j))
	  {
	    pBlock->Extend();
	  }
	else
	  {
	    AddBlock(tempBlockMapKey,
		     xStart,
		     j,
		     xEnd,
		     j+1,
		     blockIndex);
	  }
      }
  }
}

