#ifndef MENU_H
#define MENU_H
#include "graphics.h"
#include "time.h"
#include <iostream>
#include "label.h"
#include "button.h"

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
        
};

#endif
