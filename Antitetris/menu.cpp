#include "menu.h"

Menu::Menu(){
    initwindow(640,480,"AntiTetris",100,100,true,true); 
    bkcolor = LIGHTCYAN;
    
    logo.setText("AntiTetris");
    logo.setColor(bkcolor, BLUE);
    logo.setPosition(120, 10);
    logo.setSize(2);
    
    startBtn.setCaption("Start!");
    startBtn.setColor(6, GREEN);
    startBtn.setPosition(30,300);
    
    exitBtn.setCaption("Exit!");
    exitBtn.setColor(6, GREEN);
    exitBtn.setPosition(350,300);
    
    buttonIndex = 0;
    startBtn.setFocus(true);
    
    blinkVal = 100000;   
    flag = true;  
}

int Menu::start(){
    exit = false;
    status = 1;
    int frames = 500, i = 0;
    settextstyle(0,HORIZ_DIR,10);
    
    while(!exit)
    {
        while(i < frames){
            processEvents();
            update();
            i++;
        }   
        render(); 
        i = 0;
    }
    closegraph();
    return status;
}

void Menu::render(){
    cleardevice();  
    setbkcolor(bkcolor);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(0,0,getmaxx(),getmaxy());
    logo.draw();
    startBtn.draw();
    exitBtn.draw();
    swapbuffers();
}

void Menu::update(){
    time++;
    if(time > blinkVal)
    {
        logo.setColor(bkcolor, flag);
        flag = !flag;
        time = 0;
    }
}

void Menu::processEvents(){
    if(kbhit())
    {
        char key = getch();

        if(key == '\r')
        {
            if(buttonIndex)
            {
                status = 2;
                exit = true;
            }
            else
            {
                status = 1;
                exit = true;
            }
        }
        
        if(key == 27)
        {
            exit = true;
            status = 2;
        }
        
        if(key == NULL)
        {
            char keychar = getch();
            switch(keychar)
            {
                case 'M': //arrow right
                {
                    if(buttonIndex == 1)
                        buttonIndex--;
                    else if(buttonIndex == 0)
                        buttonIndex++;    
                }
                    break;
                
                case 'K': //arrow left
                {
                    if(buttonIndex == 0)
                        buttonIndex = 1;
                    else
                        buttonIndex--;  
                }
                    break;
            }
            
            if(buttonIndex == 1)
            {
                exitBtn.setFocus(true);
                startBtn.setFocus(false);
            }
            else
            {
                exitBtn.setFocus(false);
                startBtn.setFocus(true);
            }
        }
    }    
}
