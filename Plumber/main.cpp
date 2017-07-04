#include <iostream>
#include "game.h"
#include "menu.h"

int main(){
    enum gameStat{
         MENU,
         GAME,
         EXIT
    };
    
    gameStat status;
    status = MENU;
    
    while(status != EXIT)
    {
        switch(status)
        {
            case MENU:
                {
                Menu menu;
                status = static_cast<gameStat>(menu.start());
            }
            break;
            
            case GAME:
                {
                Game game;
                status = static_cast<gameStat>(game.start());
            }
            break;
            
            case EXIT:
                break;
        }   
    } 
//    closegraph();
    return 0;
}


