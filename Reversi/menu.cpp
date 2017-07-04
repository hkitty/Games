#include "menu.h"

Menu::Menu(){
    initwindow(640,480,"Reversi",100,100,true,true); 
    bkcolor = GREEN;
    
    logo.setText(" Reversi");
    logo.setColor(bkcolor, BLUE);
    logo.setPosition(140, 10);
    logo.setSize(2);
    
    startBtn.setCaption("Start!");
    startBtn.setColor(6, WHITE);
    startBtn.setPosition(200,150);
    
    exitBtn.setCaption("Exit!");
    exitBtn.setColor(6, BLACK);
    exitBtn.setPosition(200,300);
    
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
    setfillstyle(SOLID_FILL, GREEN);
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
                case 'P': //arrow right
                {
                    if(buttonIndex == 1)
                        buttonIndex--;
                    else if(buttonIndex == 0)
                        buttonIndex++;    
                }
                    break;
                
                case 'H': //arrow left
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
