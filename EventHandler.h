#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H



class SDL_Window;

//Interface to receive events from some kind of controller object.
class EventHandler
{
private:
    bool m_bQuit;
    SDL_Window* m_pWindow;
public:
    explicit EventHandler(SDL_Window *pWindow);

//Main Event Loop
    void EventLoop();

//Destructor
    virtual ~EventHandler();
    
    
};



#endif
