//https://youtu.be/N614k7LVuMU -wtf is this ?

#include "Room.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ShaderUtil.h"
#include "Block.h"
#include "BlockMapKey.h"

Room::Room(const glm::mat4& projection, const std::string& mapFileName):
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
  unsigned char rLast = pixels[2];
  int pixelRunCount = 0;
  float xPositionStart = -96.0; //TBD remove magic numbers
  float xPositionStop = -96.0;
  float yPositionStart = 54.0;
  float yPositionStop = 53.0; //TBD this will eventually be counted down
  int xStart=0;
  int pitch = map_image_surface->pitch;
  int pixelNum = 0;
  for(int j = 0; j < map_image_surface->h; ++j)

    {
      int offset = j * pitch; //offset into the byte array of pixels
      rLast = pixels[offset + 2]; //use the first red byte to start
      pixelRunCount = 0;
      xPositionStart = -96.0; //TBD remove magic numbers
      xPositionStop = -96.0;
      xStart = 0;
      for(int i = 0; i < pitch;)
	{
	  unsigned char b = pixels[offset + i++];
	  unsigned char g = pixels[offset + i++];
	  unsigned char r = pixels[offset + i++];
	  ++pixelNum;
	  //Check to see if it's still the same texture
	  if(r!=rLast || pixelNum == map_image_surface->w) //we've reached the end.  create the block object that fits this count.
	    {
		  int xEnd = xStart + pixelRunCount;
		  
		  
		  xPositionStop = xPositionStart + static_cast<double>(pixelRunCount);
	      //Block creation
	      if(rLast == 255) //Only create objects when the Red byte is 255
		{
		  //make sure the block isn't already in the map
		  //		  BlockMapKey tempBlockMapKey(xPositionStart,xPositionStop,r,g,b);
		  BlockMapKey tempBlockMapKey(xStart, xEnd,r,g,b);

		  BlockMap::iterator iter = m_blockMap.find(tempBlockMapKey);
		  
		  if(iter == m_blockMap.end())
		    {
		      AddBlock(tempBlockMapKey,
			       xPositionStart,
			       yPositionStart,
			       xPositionStop,
			       yPositionStop,
			       r,g,b,
			       j);
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
				   xPositionStart,
				   yPositionStart,
				   xPositionStop,
				   yPositionStop,
				   r,g,b,
				   j);
			}
		    }
		}
    
	      //reset
	      if(pixelNum == map_image_surface->w) //reset when we reach the end of the row
		{
		  xPositionStart = -96.0; // TBD - remove magic numbers
		  xPositionStop = xPositionStart;
		  xStart = 0;
		  pixelNum = 0;
		}
	      else //reset at the end of the run
		{
		  xPositionStart = xPositionStop;
		  xStart += pixelRunCount;
		  rLast = r;
		}
	      pixelRunCount = 1;

	    } // last in run or row
	  else
	    {
	      ++pixelRunCount;
	    }

	}
      yPositionStop--;
      yPositionStart--;
    }
  SDL_UnlockSurface(map_image_surface);    
  SDL_FreeSurface(map_image_surface);
  std::cout << "Block Map size: " << m_blockMap.size() << std::endl;

  BlockMap::iterator iter = m_blockMap.begin();
  for(;iter != m_blockMap.end(); ++iter)
    {
      iter->second->SetupGraphics();
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
		    const float leftX,
		    const float topY,
		    const float rightX,
		    const float botY,
		    const unsigned char r, const unsigned char g, const unsigned char b,
		    const unsigned int row)
{
  Block * pBlock = new Block(m_projection,
			     leftX,
			     topY,
			     rightX,
			     botY,
			     r,g,b,
			     row);
  m_blockMap[blockMapKey]= pBlock;
}
