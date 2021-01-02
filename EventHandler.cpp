#include "GLHeader.h"
#include "EventHandler.h"
#include <SDL2/SDL.h>
#include <iostream>

#include "Room.h"

EventHandler::EventHandler(SDL_Window *pWindow):
    m_bQuit(false),
    m_pWindow(pWindow)
{
}

//Main Event Loop
void EventHandler::EventLoop()
{
  //TBD - This should probably be either passed in or created dynamically
  //Rooms are 192x108 grid
  Room room(glm::ortho(-96.0,95.0,-54.0,53.0),"grid.bmp");
  
  SDL_Event event;
  while(!m_bQuit)
    {
      if(SDL_PollEvent(&event))
        {          
	  switch(event.type)
            {
                case SDL_QUIT:
                    m_bQuit=true;
                    break;
                case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_X:
                            m_bQuit=true;
                            break;
                        case SDL_SCANCODE_A:
                            break;
                        case SDL_SCANCODE_S:
                            break;
                        case SDL_SCANCODE_D:
                            break;                            
                        case SDL_SCANCODE_W:
                            break;
                    }
                    break;
                }
               
                default:
                    break;
            }
        }

        
        //clear the screen
        glClear( GL_COLOR_BUFFER_BIT );
	room.Draw();
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
    

