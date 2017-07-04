#include "menu.h"

Menu::Menu(){
    initwindow(640,480,"Plumber",100,100,true,true); 
    
    logo.setText("Plumber");
    logo.setColor(COLOR(200,225,255), COLOR(102,205,170));
    logo.setPosition(185, 90);
    logo.setSize(0);
    
    startBtn.setVisible(true);
    startBtn.setCaption("Start!");
    startBtn.setColor(COLOR(200,225,255), COLOR(102,205,170));
    startBtn.setPosition(30,280);
    
    exitBtn.setCaption("Exit!");
    exitBtn.setColor(COLOR(200,225,255), COLOR(102,205,170));
    exitBtn.setPosition(350,280);
    
    pipe = new Pipe(1, 130, 44);
    pipe->setDirection(1);
    
    pipe2 = new Pipe(0, 196, 44);
    pipe2->setDirection(1);
    
    pipe3 = new Pipe(0, 262, 44);
    pipe3->setDirection(1);
    
    pipe4 = new Pipe(0, 328, 44);
    pipe4->setDirection(1);
    
    pipe5 = new Pipe(0, 394, 44);
    pipe5->setDirection(1);
    
    pipe6 = new Pipe(1, 460, 44);
    pipe6->setDirection(2);
    
    pipe7 = new Pipe(1, 460, 110);
    pipe7->setDirection(0);
    
    pipe8 = new Pipe(1, 130, 110);
    pipe8->setDirection(3);
    
    pipe9 = new Pipe(0, 526, 110);
    pipe9->setDirection(1);
    
    pipe10 = new Pipe(0, 592, 110);
    pipe10->setDirection(1);
    
    pipe11 = new Pipe(0, 64, 110);
    pipe11->setDirection(1);
    
    pipe12 = new Pipe(0, -2, 110);
    pipe12->setDirection(1);
    
    buttonIndex = 0;
    startBtn.setFocus(true);
    time = 1000;

       
    flag = true;  
    settextstyle(10, 0, 7);
}

int Menu::start(){
    exit = false;
    status = 1;
    int frames = 500, i = 0;

    
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
    setfillstyle(SOLID_FILL, COLOR(200,225,255));
    bar(0,0,getmaxx(),getmaxy());
    
    setcolor(COLOR(164,211,238));
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    
    
    setbkcolor(COLOR(200,225,255));

    setcolor(COLOR(126, 192,238));
    logo.draw();
    
    pipe->draw();
    pipe2->draw();
    pipe3->draw();
    pipe4->draw();
    pipe5->draw();
    pipe6->draw();
    pipe7->draw();
    pipe8->draw();
    pipe9->draw();
    pipe10->draw();
    pipe11->draw();
    pipe12->draw();
    
    startBtn.draw();
    exitBtn.draw();
    
    swapbuffers();
}

void Menu::update(){

}

void Menu::processEvents(){
    
    if ( ismouseclick(WM_LBUTTONDOWN) ) {
        int mouseX, mouseY;
        
        getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
        
        if ( startBtn.isClick(mouseX, mouseY) ) {
            status = 1;
            exit = true;
        }
        if ( exitBtn.isClick(mouseX, mouseY) ) {

            status = 2;
            exit = true;
        }
    }
    
    
    
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
