#include "game.h"

Game::Game()
{
    initwindow(650,468,"Play Plumber",100,100,true,true);
    srand(time(0));
    

    initPipes(); //����������� �����


    game = true;
    
    
    //======================������� ������� � ������ �� ����
    winLabel = new Label();
    winLabel->setColor(COLOR(100,149,237), COLOR(102,205,170));
    winLabel->setText("You LOSE");
    winLabel->setVisible(false);
    winLabel->setPosition(150, 30);
    
    
    exitBtn = new Button();
    exitBtn->setVisible(false);
    exitBtn->setCaption("   Exit");
    exitBtn->setColor(COLOR(100,149,237), COLOR(102,205,170));
    exitBtn->setPosition(10,340);
    //======================
    
    //======================������� ������
    timeToEnd = new Label();
    timeToEnd->setColor(COLOR(100,149,237), COLOR(102,205,170));
    timeToEnd->setText("1:30 left...");
    timeToEnd->setVisible(true);
    timeToEnd->setPosition(10, 360);
    
    gameTime.tm_sec = 60;
    startTime = time(NULL);
    //======================
}

int Game::start()
{
    exit = false;
    
    while ( !exit ) {
        delay(100);
        processEvents();
        update();
        render();
    }
    
    closegraph();
    return 0;
}

void Game::processEvents()
{
    if ( kbhit() || ismouseclick(WM_LBUTTONDOWN) )
    {      
        if(kbhit()) {
            char key = getch();
            if(key == 27) 
            {
                exit = true;
            } if ( key == '\r' )
            {
                checkWay();
            }
        }
        
        int mouseX, mouseY;
        
        //======================�������������� � ������� ����
        getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY); 
        if ( game ) {
            if ( mouseX > 66 && mouseX < 594 && mouseY > 66 && mouseY < 330 ) { 
                
                int posX, posY;
    
                double a, b, xx, yy;
            
                a = mouseX/66;
                b = mouseY/66;
            
                std::modf(a, &xx);
                std::modf(b, &yy);
            
                posX = (int)xx - 1;
                posY = (int)yy - 1;
                
                
                std::vector<Pipe*>::iterator it;
                it = pipes.begin();
                
                //======================������� ����� �� ������� ��������
                while ( it != pipes.end() ) { 
                    if ( (*it)->getRelX() == posX && (*it)->getRelY() == posY ) { 
                        (*it)->rotate(); // ������������ ��
                    }
                
                it++;
                }
                
            }
            //======================����� �������� �� ����� (��������� ����)
            if ( mouseX > 73 && mouseX < 124 && mouseY > 5 && mouseY < 54 ) { 
                checkWay(); //��������� ���� ���� �� ������������
            }
            
            
        } else {
            //====================== ����� ���������� ������ ������������ ������� �� ������ ������
                
             if ( exitBtn->isClick(mouseX, mouseY) ) {
                exit = true;
            }
        }
    }
}

void Game::render()
{
    
    //======================��������� ���� �����
    setfillstyle(SOLID_FILL, COLOR(230,225,255)); 
    bar(0,0,getmaxx(),getmaxy());
    //======================


    //======================������ ���� � ����� �����-������
    setcolor(0);
    setfillstyle(SOLID_FILL, COLOR(0,0,255)); 
    drawDecor();
    
    setcolor(COLOR(0,0, 150));
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    for(int i = 0; i <= 8; i++) {
        line(66 + i*66, 66, 66 + i*66, 330);       
    } 
    
    for ( int i = 0; i < 5; i++ ) {
         line(66, 66 + i*66, 594, 66 + i*66);
    }
    
    //======================
    
    
    //======================������ ����� �� ����
    std::vector<Pipe*>::iterator it;
    it = pipes.begin();
    

    setcolor(0);
    setfillstyle(SOLID_FILL, COLOR(0,0,255)); 
    while ( it != pipes.end() ) {
    
        (*it)->draw();
     
    it++;   
    }
    
    //======================
    
    
    //======================������ �������, ������ � ������ ������
    settextstyle(10, 0, 8);
    setbkcolor(COLOR(230,225,255));
    winLabel->draw();
    
    settextstyle(10, 0, 6);
    setbkcolor(COLOR(230,225,255));
    timeToEnd->draw();
    
    setbkcolor(COLOR(100,149,237));
    settextstyle(10, 0, 5);

    exitBtn->draw();
    //======================
    
    
    swapbuffers(); //������� ������
}

void Game::update()
{
    //======================���������� �������� �������
    
    currTime = time(NULL);
    passedTime = difftime(startTime, currTime);
    std::stringstream ss;
    ss << gameTime.tm_sec + passedTime;
    std::string str = ss.str();
    timeToEnd->setText(str+ " sec left...");
    //======================
    //======================���� ����� ����� - ��������� ����, ��������� ����
    
    if(passedTime < -60 && game)
        {
            checkWay();
        }
    //======================
}

void Game::initPipes() 
{
    //======================������� ����
    
    level1 = new bool* [8];
    
    for(int count = 0; count < 8; count++) {
            level1[count] = new bool[4];
    } 
    //======================
    
    //======================��������� �������
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            level1[i][j] = 1;
        }
    }
    
    level1[0][0] = 0;
    level1[0][2] = 0;
    level1[0][6] = 0;
    level1[1][0] = 0;
    level1[1][2] = 0;
    level1[1][4] = 0;
    level1[1][6] = 0;
    level1[2][2] = 0;
    level1[2][4] = 0;
    level1[2][5] = 0;
    level1[3][3] = 0;
    
    
    //======================
    
    //======================������� ������ ����� � ������� � ������ ��� ��������� ���������
    Pipe *temp;
    
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
                temp = new Pipe(level1[i][j], 66 + i*66, 66 + j * 66);
                temp->setRelPos(i, j);
                
                pipes.push_back(temp);
        }
    }
    //======================
}

void Game::checkWay() 
{

    timeToEnd->setVisible(false);
    
    
    //======================�������� ����
    //======================����� ������� ������� (�����) � ������� ������� �� �����
    int nextX, nextY;
    int currX = 0;
    int currY = 0;
    
    bool flag = false;
    
    
    //======================����� ������ ������� � ������� �� ��� ������
    //======================���� ���� ���� � ����� ������ ���� ������� ������ �����, ������ ��������� �� ��������� �������
    
    if ( pipes.front()->getNode1X() == 0 && pipes.front()->getNode1Y() == -1 ) {
        nextX = pipes.front()->getNode2X();
        nextY = pipes.front()->getNode2Y();
        flag = true;
        
        pipes.front()->setFilled(true);
    }
    if ( pipes.front()->getNode2X() == 0 && pipes.front()->getNode2Y() == -1) {
        nextX = pipes.front()->getNode1X();
        nextY = pipes.front()->getNode1Y();
        flag = true;
        
        pipes.front()->setFilled(true);
    }
    
    
    //======================���������� �� ������� ����


    std::vector<Pipe*>::iterator it;    
    
    while ( nextX != 7 && nextY != 4 && flag) {
        
        it = pipes.begin();
        flag = false;
        
        //======================����� ���� ����� ������, ��������� � ��������, ���� � ���������� �������� ����� ����� ���������
        //======================� ������ ������ ����������� - ���� ������
        //======================� ��� ���� �� ������ �� ����� ������, ���� ��� ������� ����� �������� -
        //======================������� ��������� � ������, ���� ��� - � ���������
        while ( it != pipes.end() ) {
            if ( (*it)->getRelX() == nextX && (*it)->getRelY() == nextY ) {
                flag = false;
                
                if ( (*it)->getNode2X() == 7 && (*it)->getNode2Y() == 4 || (*it)->getNode1X() == 7 && (*it)->getNode1Y() == 4 ) {
                    winLabel->setText("You WIN!");
                }
                    
                if ( (*it)->getNode1X() == currX && (*it)->getNode1Y() == currY ) {
                    nextX = (*it)->getNode2X();
                    nextY = (*it)->getNode2Y();
                    flag = true;
                    (*it)->setFilled(true);
                    
                    currX = (*it)->getRelX();
                    currY = (*it)->getRelY();
                } 
                
                if ( (*it)->getNode2X() == currX && (*it)->getNode2Y() == currY ) {
                    nextX = (*it)->getNode1X();
                    nextY = (*it)->getNode1Y();
                    flag = true;
                    (*it)->setFilled(true);
                    
                    currX = (*it)->getRelX();
                    currY = (*it)->getRelY();
                }
            } 
        it++;
        }
        
        if ( !flag ) {
            
            winLabel->setText("You LOSE");
        }
    }
    winLabel->setVisible(true);
    
    exitBtn->setVisible(true);
    filled = true;
                    
    game = false;
}

void Game::drawDecor()
{
    
    //======================��������� ����� ����� � ����� ������
    if(filled)
    {
        bar(84, 59, 114, 66);
        bar(66*8 + 18, 66*5, 66*8 + 48, 66*5 + 7);
        bar(88,59,108, -2);    
        bar(66*8 + 43, 66*5 + 57, 66*8 + 150, 66*5 + 37);
        bar(66*8 + 23, 66*5 + 7, 66*8 + 43, 66*5 + 57);
    }
    //------Enter
    rectangle(84, 59, 114, 66);
    rectangle(89, 59, 109, -2);
    
    circle(99, 30, 25);
    circle(99, 30, 22);
    circle(99, 30, 24);
    circle(99, 30, 20);
    circle(99, 30, 2);
    circle(99, 30, 4);
    circle(99, 30, 6);

    line(95, 10, 95, 48);
    line(102, 10, 102, 48);
    line(97, 10, 97, 48);
    line(100, 10, 100, 48);

    line(79, 28, 115, 28);
    line(79, 30, 115, 30); 
    line(79, 28, 115, 28);
    line(79, 32, 115, 32); 
    
    
    //------Exit
    rectangle(66*8 + 18, 66*5, 66*8 + 48, 66*5 + 7);
    line(66*8 + 23, 66*5 + 7, 66*8 + 23, 66*5 + 57);
    line(66*8 + 43, 66*5 + 7, 66*8 + 43, 66*5 + 37);
    line(66*8 + 43, 66*5 + 37, 66*8 + 150, 66*5 + 37);
    line(66*8 + 23, 66*5 + 57, 66*8 + 150, 66*5 + 57);  
    
    //======================
}
    
Game::~Game()
{
}
