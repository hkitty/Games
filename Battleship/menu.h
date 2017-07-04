#ifndef MENU_H
#define MENU_H
#include "graphics.h"
#include "time.h"
#include <iostream>
#include "label.h"
#include "button.h"
#include "math.h"

#define dx 10 // шаг сетки по X 
#define dy 10 // шаг сетки по Y

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
        void ship(int x, int y);
         
        int buttonIndex;
        Label logo; 
        Button startBtn, exitBtn;
        int time, blinkVal, bkcolor;
        int x, y;
        bool flag;
        
};

#endif
