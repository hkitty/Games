#ifndef MENU_H
#define MENU_H
#include "graphics.h"
#include "time.h"
#include <iostream>
#include "label.h"
#include "button.h"
#include "math.h"
#include "pipe.h"

class Menu{
public:
       Menu();
       int start();

private:
        int status;
        bool exit;
        void render();
        void update();
        void processEvents(); 
         
        int buttonIndex;
        Label logo; 
        Button startBtn, exitBtn;
        int time, blinkVal, bkcolor;
        
        bool flag;
        
        Pipe *pipe, *pipe2, *pipe3, *pipe4, *pipe5, *pipe6, *pipe7, *pipe8, *pipe9, *pipe10, *pipe11, *pipe12;
        
};

#endif
