#include "GLHeader.h"
#include "EventHandler.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <Box2D/Box2D.h>

#include "Room.h"
#include "Ship.h"
#include "tinyxml2.h"
#include "Shaders.h"

EventHandler::EventHandler(SDL_Window *pWindow, b2World& physicsWorld):
    m_bQuit(false),
    m_pWindow(pWindow),
    m_physicsWorld(physicsWorld),
    m_timeStep(1.0f / 60.0f),
    m_velocityIterations(6),
    m_positionIterations(2)
{
}

//Main Event Loop
void EventHandler::EventLoop()
{


  //Example code for loading a dummy xml file
  tinyxml2::XMLDocument doc;
  tinyxml2::XMLError errorCode = doc.LoadFile("dummy.xml");
  if (errorCode != tinyxml2::XML_SUCCESS)
    {
      std::cerr << "Error loading XML file" << std::endl;
    }
#ifdef TINYXML  
  else
    {
      //Note that the root element may not actually have any value of its own
      //it could just be the root of the document
      //use named children to get specific elements
      tinyxml2::XMLNode *pRoot = doc.RootElement();
      if(!pRoot)
	{
	  std::cerr << "Error getting root element" << std::endl;
	}
      else
	{
	  //Using a named child to get an element
	  tinyxml2::XMLElement *pElement = pRoot->FirstChildElement("roomId");
	  if(!pElement)
	    {
	      std::cerr << "Error getting roomId" << std::endl;
	    }
	  else
	    {
	      //Translating the data from a named element into an integer
	      int roomId = 0;
	      pElement->QueryIntText(&roomId);
	      std::cerr << "Found roomId: " << roomId << std::endl;
	    }

	  pElement = pRoot->FirstChildElement("someFloat");
	  if(!pElement)
	    {
	      std::cerr << "Error getting someFloat" << std::endl;
	    }
	  else
	    {
	      //Translating the data from a named element into an float
	      float someFloat = 0;
	      pElement->QueryFloatText(&someFloat);
	      std::cerr << "Found someFloat: " << someFloat << std::endl;

	      //Or just getting the value as text.  Note that this must be a const char*
	      const char *pChar = pElement->GetText();
	      std::cout << "Text string of someFloat: " << pChar << std::endl;

	      //Loop through the all the element (note unnamed child)
	      pElement = pRoot->FirstChildElement();
	      while(pElement != 0 )
		{
		  const char *pChar = pElement->GetText();
		  std::cout << "Text string: " << pChar << std::endl;
		  pElement = pElement->NextSiblingElement();
		}

	      //iterate through named elements
	      pElement = pRoot->FirstChildElement("roomId");
	      while(pElement != 0 )
		{
		  const char *pChar = pElement->GetText();
		  std::cout << "RoomId string: " << pChar << std::endl;
		  //and get the next named sibling
		  pElement = pElement->NextSiblingElement("roomId");
		}
	      

	    }

	  
	}
    }
#endif



  Shaders shaders;
  
  //TBD - This should probably be either passed in or created dynamically
  //Rooms are 192x108 grid
  Room room(m_physicsWorld,
	    glm::ortho(-96.0,95.0,-54.0,53.0),
	    shaders,
	    "grid.bmp");

  Ship myShip(m_physicsWorld,
	      glm::ortho(-96.0,95.0,-54.0,53.0));
  unsigned int command = 0;
  bool bShipCommand = false;
  SDL_Event event;
  while(!m_bQuit)
    {
      bShipCommand = false;
      if(SDL_PollEvent(&event))
        {          
	  switch(event.type)
            {
	    case SDL_QUIT:
	      m_bQuit=true;
	      break;
	    case SDL_KEYDOWN:
	      {
		bShipCommand = true;
		switch(event.key.keysym.scancode)
		  {
		  case SDL_SCANCODE_X:
		    m_bQuit=true;
		    break;
		  case SDL_SCANCODE_A: //left
		    command |= SHIP_CCW;
		    break;
		  case SDL_SCANCODE_D: //right
		    command |= SHIP_CW;
		    break;
		  case SDL_SCANCODE_W: //up
		    command |= SHIP_FORWARD;
		    break;
		  case SDL_SCANCODE_S: //shoot
		    //		    command |= SHIP_SHOOT;
		    break;
		  }
		break;
	      }
	      
	    case SDL_KEYUP:
	      {
		bShipCommand = true;
		switch(event.key.keysym.scancode)
		  {
		  case SDL_SCANCODE_A: //left
		    command &= ~SHIP_CCW;
		    break;
		  case SDL_SCANCODE_D: //right
		    command &= ~SHIP_CW;
		    break;
		  case SDL_SCANCODE_W: //up
		    command &= ~SHIP_FORWARD;
		    break;
		  case SDL_SCANCODE_S: //shoot
		    //		    command &= ~SHIP_SHOOT;
		    break;
		  }
		break;
	      }
	    default:
                    break;
            }
        }


      if(bShipCommand)
	{
	  myShip.ProcessInput(command);
	}
      
      m_physicsWorld.Step(m_timeStep, m_velocityIterations, m_positionIterations);
      
      //clear the screen
      glClear( GL_COLOR_BUFFER_BIT );
      room.Draw();
      myShip.DoCommands();
      myShip.Draw();
      //Display the back buffer
      SDL_GL_SwapWindow(m_pWindow);
      
      //Sleep to not eat the machine
      SDL_Delay(60);
    }
    
}

//Destructor
EventHandler::~EventHandler()
{
};
    

