#include "game.h"

Game::Game()
{
    initwindow(650,468,"Play BattleShip",100,100,true,true);

    //====================�������� � ��������� ���������� �������� �� ����=========
    settextstyle(10, 0, 9);
    setbkcolor(COLOR(200,225,255));
    
    label = new Label();
    label->setColor(COLOR(200,225,255), COLOR(102,205,170));
    label->setVisible(false);
    label->setPosition(40, 150);
    
    settextstyle(10, 0, 7);
    setbkcolor(COLOR(200,225,255));
    
    esc = new Label();
    esc->setColor(COLOR(200,225,255), COLOR(0,0,150));
    esc->setText("Press Esc to return in the menu");
    esc->setPosition(40, 235);
    esc->setVisible(false);
    
    settextstyle(7, 0, 3);
    setbkcolor(COLOR(230,225,255));
    
    republic = new Label();
    republic->setColor(COLOR(200,225,255), COLOR(0,0,150));
    republic->setPosition(24, 30);
    republic->setText("R e s p u b l i k a");
    republic->setVisible(true);
    
    l1 = new Label();
    l1->setColor(COLOR(200,225,255), COLOR(0,0,150));
    l1->setVisible(true);
    
    republic2 = new Label();
    republic2->setColor(COLOR(200,225,255), COLOR(0,0,150));
    republic2->setPosition(364, 30);
    republic2->setText("R e s p u b l i k a");
    republic2->setVisible(true);
    
    stat = new Label();
    stat->setColor(COLOR(200,225,255), COLOR(0,0,150));
    stat->setPosition(145, 342);
    stat->setText("Set up ships...");
    stat->setVisible(true);
    
    info = new Label();
    info->setColor(COLOR(200,225,255), COLOR(0,0,150));
    info->setPosition(145, 394);
    info->setText("Press Space to rotate");
    info->setVisible(true);
    
    //==============================================================================
    SIZE = 10;
    
    status = false;
    waitForPlayer = false;
    
    playerWin = false;
    AIWin = false;
    
    srand(time(0));
    
    
    //===============================�������� ����� ������ � ���������� � ���������� �� ������� ��������============
    playerField = new int* [SIZE];
    AIField = new int* [SIZE];
    matrix = new int* [4];
    
    for(int count = 0; count < SIZE; count++) {
            playerField[count] = new int[SIZE];
            AIField[count] = new int[SIZE];
    }       
    
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            playerField[i][j] = 0;
            AIField[i][j] = 0;
        }
    }
    //=========================�������� � ���������� ���������� ����(4�4) ������� ����������
    for ( int i = 0; i < 4; i++ ) {
            matrix[i] = new int[4];
    }
    
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            matrix[i][j] = 0;
        }
    }
    
    
    
    //====== ������ ������ ��������, ����� ����� ������������ ��� ��� �����������
    ship = new Ship(matrix, 1);
    
    initAIField();
    
    ships.push_back(1);
    ships.push_back(1);
    ships.push_back(1);
    ships.push_back(1);
    
    ships.push_back(2);
    ships.push_back(2);
    ships.push_back(2);
    
    ships.push_back(3);
    ships.push_back(3);
    
    ships.push_back(4);
    
    //=======================================================================================
}

int Game::start()
{
    exit = false;
    
    int frames = 50000, i = 0;
    
    while(!exit) {
        delay(100);
        processEvents(); //�������������� � �������������
        update(); // ���������� ����������
        render(); // ���������
    }
    
    closegraph();
    return 0;
}

void Game::processEvents()
{
    if(kbhit() || ismouseclick(WM_LBUTTONDOWN)) // ��������� ��� ������� ������ ���������� ��� ���� � ��������� ������������ �������� ����� �� ��������
    {      
        if(kbhit()) {
            char key = getch();
            if(key == 27) // ��� ������� Esc ������� � ����
            {
                exit = true;
            } 
            if ( key == ' ' ) { // ��� ������ ������� 
                if ( !status ) { // � ���� ���� ��� �� ������ -
                    if ( waitForPlayer ) {
                        for (int i = 0; i < 4; i++ ) {
                            for ( int j = 0; j < 4; j++ ) {
                                matrix[i][j] = 0;
                            }
                        }
                        
                        ship->rotate(); // ������������ �������
                        ship->draw(); // � ������������ ��� �� ��������� ����
                        
                    }
                }
            }
        } else {
            int mouseX, mouseY;
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            
            
            if ( status ) { //���� � ����
                if (waitForPlayer) { // � ��� ������
                    if ( mouseX > 364 && mouseX < 624 && mouseY > 56 && mouseY < 312 ) { //��������� ���������� �����
                        //========== ����������� ������� � �������, ���� �������� ������
                        double a, b, xx, yy;
                    
                        a = mouseX/26;
                        b = mouseY/26;
                    
                        std::modf(a, &xx);
                        std::modf(b, &yy);
                    
                        x = (int)xx - 1 - 13;
                        y = (int)yy - 1 - 1;
                        //==================================================================
                        if ( shoot(x, y, AIField) ) { //��������
                            waitForPlayer = false; // �������� ��� ����������
                        }
                    }
                    
                    
                }
            } else {
                if (waitForPlayer) { // ����� - �� � ���� (� ������ ����������� ��������) � ��� ������
                    if ( mouseX > 26 && mouseX < 294 && mouseY > 56 && mouseY < 312 ) { //��� �� �������� ���������� � ����� ����������� ���� ������ � �������
                        
                        double a, b, xx, yy;
                        
                        a = mouseX/26;
                        b = mouseY/26;
                    
                        std::modf(a, &xx);
                        std::modf(b, &yy);
                    
                        x = (int)xx - 1;
                        y = (int)yy - 1 - 1;
                        
                        ship->setField(playerField, 10); 
                        ship->setCoordinates(x, y); //������ ������� ���� �������� ������
                        
                        if ( ship->draw() ) { // ������ ���
                            ships.pop_back(); //����� �� ������ ��������� �������
                        }
    
                        waitForPlayer = false;
                    }
                }
            }
        }
    }
}

void Game::render()
{
    setfillstyle(SOLID_FILL, COLOR(230,225,255)); // ���������� ����
    bar(0,0,getmaxx(),getmaxy()); // ������ ���
    
    settextstyle(7, 0, 3); 
    setbkcolor(COLOR(230,225,255)); 
           
    republic->draw(); // 
    republic2->draw(); // ��������� �������� "����������" 
    
    
    //==================��������� ���� ����� ������ (�� 1 �� 10)
    for ( int i = 0; i < 10; i++ ) {
        l1->setPosition(315, 56 + i*26);
        char ww[3];
        itoa(i + 1,ww,10);
        l1->setText(ww);
        l1->draw();
    } 
    
    //=============================================================
    
    
    //=======================������ �����================
    setcolor(COLOR(164,211,238));
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    for ( int i = 0; i < 25; i++ ) {
        line(i*26, 0, i*26, 466);
        line(0, i*26, 648, i*26);
    }
    //====================================================
    
    
    //===================������ 2 ����================
    setcolor(COLOR(0,0, 150));
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    for(int i = 0; i <= SIZE; i++) {
        line(26 + i*26, 52, 26 + i*26, 312);
        line(26, 52 + i*26, 286, 52 + i*26);
        
        line(364 + i*26, 52, 364 + i*26, 312);
        line(364, 52 + i*26, 624, 52 + i*26);
        
    }
    //==================================================
    
    
    //=================������ ��������� ���� �����===============
    for ( int i = 0; i <= 4; i++ ) {
            line(26 + i*26, 338, 26 + i*26, 442);
            line(26, 338 + i*26, 130, 338 + i*26);
    }
    //===========================================================
    

    //======================������ ������� �� ��������� ����===============
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            if ( matrix[i][j] == 1 ) {
                setfillstyle(SOLID_FILL, COLOR(104, 131, 139));
                bar(28 + i*26, 314 + (j+1)*26, 26 + i*26 + 25, 312 + (j+1)*26 + 25);
            }
        }
    }
    //=================================================================
    
    
    //==========================��������� �������� � ��������� �� ���� ������==================
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            if ( playerField[i][j] == 1 ) { 
                setfillstyle(SOLID_FILL, COLOR(104, 131, 139));
                bar(28 + i*26, 28 + (j+1)*26, 26 + i*26 + 25, 26 + (j+1)*26 + 25);
            }
            if ( playerField[i][j] == -1 ) {
                setfillstyle(SOLID_FILL, COLOR(104, 131, 139));
                bar(28 + i*26, 28 + (j+1)*26, 26 + i*26 + 25, 26 + (j+1)*26 + 25);
                line(28 + i*26, 28 + (j+1)*26, 26 + i*26 + 25, 26 + (j+1)*26 + 25);
                line(28 + i*26 + 22, 28 + (j+1)*26, 26 + i*26 + 1, 26 + (j+1)*26 + 25);
            }
            if ( playerField[i][j] == -2 ) {
                setfillstyle(SOLID_FILL, COLOR(255, 131, 139));
                bar(28 + i*26, 28 + (j+1)*26, 26 + i*26 + 25, 26 + (j+1)*26 + 25);
                line(28 + i*26, 28 + (j+1)*26, 26 + i*26 + 25, 26 + (j+1)*26 + 25);
                line(28 + i*26 + 22, 28 + (j+1)*26, 26 + i*26 + 1, 26 + (j+1)*26 + 25);
            }
            if ( playerField[i][j] == 2 ) {
                setfillstyle(SOLID_FILL, COLOR(104, 131, 139));
                fillellipse(28 + i*26 + 12, 28 + (j+1)*26 + 12, 5, 5);
            } 
        }   
    }
    //=======================================================================================
    
    //===========================��������� �������� � ��������� �� ���� ���������====================
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            if ( AIField[i][j] == -1 ) {
                setfillstyle(SOLID_FILL, COLOR(104, 131, 139));
                bar(366 + i*26, 28 + (j+1)*26, 364 + i*26 + 25, 26 + (j+1)*26 + 25);
                line(366 + i*26, 28 + (j+1)*26, 364 + i*26 + 25, 26 + (j+1)*26 + 25);
                line(366 + i*26 + 22, 28 + (j+1)*26, 364 + i*26 + 1, 26 + (j+1)*26 + 25);
            }
            if ( AIField[i][j] == -2 ) {
                setfillstyle(SOLID_FILL, COLOR(255, 131, 139));
                bar(366 + i*26, 28 + (j+1)*26, 364 + i*26 + 25, 26 + (j+1)*26 + 25);
                line(366 + i*26, 28 + (j+1)*26, 364 + i*26 + 25, 26 + (j+1)*26 + 25);
                line(366 + i*26 + 22, 28 + (j+1)*26, 364 + i*26 + 1, 26 + (j+1)*26 + 25);
            }
            if ( AIField[i][j] == 2 ) {
                setfillstyle(SOLID_FILL, COLOR(104, 131, 139));
                fillellipse(366 + i*26 + 12, 28 + (j+1)*26 + 12, 5, 5);
            }
        }   
    }
    
    //==============================================================================
    
    
    //=====��������� ������==========
    settextstyle(10, 0, 2);
    setbkcolor(COLOR(230,225,255));
    info->draw();
    stat->draw();
    
    settextstyle(10, 0, 9);
    setbkcolor(COLOR(200,225,255));
    label->draw();
    settextstyle(9, 0, 4);
    esc->draw();
    //==============================
    
    swapbuffers(); //������� ������
}

void Game::update()
{
    if ( status ) { //���� � ����
        stat->setText("Shoot! ");
        info->setText(" ");
        if(!waitForPlayer) //���� ��� ����������
        {
            if ( shoot(rand()%10, rand()%10, playerField) ) { //��������
                waitForPlayer = true; //�������� ��� �������
            }
        }
        playerWin = true;
        AIWin = true;
        //�������� �� ������ 
        for ( int i = 0; i < SIZE; i++ ) {
            for ( int j = 0; j < SIZE; j++ ) {
                if ( AIField[i][j] == 1 ) {
                    playerWin = false;
                }
                
                if ( playerField[i][j] == 1 ) {
                    AIWin = false;
                }
            }
        }
        //==============� � ����������� �� ����� ����� ��� �������=======
        if ( playerWin ) {
            label->setText("You WIN!!!");
            label->setVisible(true);
            esc->setVisible(true);
            
        }
        
        if ( AIWin ) {
            label->setText("You LOSE!!!");
            label->setVisible(true);
            esc->setVisible(true);
        }
        //=================================================================
        
    } else { //���� �� � ����
        if ( !waitForPlayer ) {
            if ( !ships.empty() ) { //���� �� ����������� ��� �������
                ship->setField(matrix, 4);
                ship->setSize(ships.back());
                for(int i = 0; i < 4; i++)
                    for(int j = 0; j < 4; j++)
                        matrix[i][j] = 0;
                ship->setCoordinates(0,0); // ������ �������
                ship->draw(); // ������ ���
                waitForPlayer = true;
            } else { 
                status = true;
                waitForPlayer = true;
            }
        }
    }
}

void Game::initAIField() 
{
    
    //=====��������� ������ ��������=====
    
    ships.push_back(1);
    ships.push_back(1);
    ships.push_back(1);
    ships.push_back(1);
    
    ships.push_back(2);
    ships.push_back(2);
    ships.push_back(2);
    
    ships.push_back(3);
    ships.push_back(3);
    
    ships.push_back(4);
    //=======================================
    
    //=============����������������� ����������� �������� ����������=============
    ship->setField(AIField, 10);
    while ( !ships.empty() ) {
        ship->setSize(ships.back());
        ship->setCoordinates(rand()%9,rand()%9);
        bool rotate = rand()%2;
        
        if(rotate)
        {
            ship->rotate();
        }
        if(ship->draw())
        {
            ships.pop_back();
        }
    }
    
    //============================================================================
}

bool Game::shoot(int _x, int _y, int** fld) 
{    
    //======��������� ���������========
    if ( fld[_x][_y] != 2 && fld[_x][_y] != -1 ) { //���� � ����� ��� �� �������� � ��� ��� ��������� �������
        if ( fld[_x][_y] == 0 ) { // ���� ������ ������ 
            fld[_x][_y] = 2; //������ �����
            return true;
        }
        if ( fld[_x][_y] == 1 ) { //���� ����� �������
            fld[_x][_y] = -1; //������
            checkIfDead(_x,_y,fld); //�������� �� ���� �� �������
            return false;
        }
    } else { 
        return false;
    }
    //=================================
}

bool Game::checkIfDead(int _x, int _y, int** fld)
{  
    std::vector<pos*> ppos;
    ppos.clear();
    pos* temp;
    int posX, posY;

    temp = new pos;
    temp->x = _x;
    temp->y = _y;
    ppos.push_back(temp);

    bool upOk = true, downOk = true, leftOk = true, rightOk = true;
    
    for(int i = 1; i < 4; i++)
    {
        //--------- ������� ���� �� ������ ����� �������
        if(_x+i <= 9 && rightOk)
        {
            if(fld[_x+i][_y] == 1 ) {
                return 0;
            }
            if(fld[_x+i][_y] == 2 || fld[_x+i][_y] == 0) {
                rightOk = false;
            }
            
            if(fld[_x+i][_y] == -1 && rightOk) {
                temp = new pos;
                temp->x = _x+i;
                temp->y = _y;
                ppos.push_back(temp);
            }
        }
        //---------- ������� ���� �� ����� ����� �������
        if(_x-i >= 0 && leftOk) 
        {      
            if(fld[_x-i][_y] == 1) {
                return 0;
            }
            if(fld[_x-i][_y] == 2 || fld[_x-i][_y] == 0) {
                leftOk = false;
            }  
            if(fld[_x-i][_y] == -1 && leftOk) {
                temp = new pos;
                temp->x = _x-i;
                temp->y = _y;
                ppos.push_back(temp);
            }
        }
        //---------- ������ ���� �� ����� ����� �������
        if(_y+i<=9 && downOk)
        {      
            if(fld[_x][_y+i] == 1) {
                return 0;
            }
            if(fld[_x][_y+i] == 2 || fld[_x][_y+i] == 0) {
                downOk = false;
            }       
            if(fld[_x][_y+i] == -1 && downOk) {
                temp = new pos;
                temp->x = _x;
                temp->y = _y+i;
                ppos.push_back(temp);
            } 
        }
        //---------- ������� ���� �� ������ ����� �������
        if(_y-i>=0 && upOk)
        {
            if(fld[_x][_y-i] == 1) {
                return 0;
            }
            if(fld[_x][_y-i] == 2 || fld[_x][_y-i] == 0) {
                upOk = false;
            }
            if(fld[_x][_y-i] == -1 && upOk) {
                temp = new pos;
                temp->x = _x;
                temp->y = _y-i;
                ppos.push_back(temp);
            } 
        } 
        
        //���� ��� ����� �������, ���� ��� ��� ������ - ������� � ������ ��� ���������� � ����� ������������ ������ ������� � ������� �� ������� ���� ������ ��������
        //���� �� ���� � ����� �� ������� ��������� ����� ����� ������� - ������� �� �������
    }
    
    while (!ppos.empty()) {
        pos* tmp;
        tmp = new pos;
        
        tmp = ppos.back();
        posX = tmp->x - 1;
        posY = tmp->y - 1;
        for(int i = 0; i < 3; i++) 
            for(int j = 0; j < 3; j++)
            {
                if(posX + i < 0 || posY + j < 0 || posX + i > 9 || posY + j > 9)
                {
     
                }
                else 
                {
                    if(fld[posX + i][posY + j] == 0)  
                         fld[posX + i][posY + j] = 2;
                         
                    if(fld[posX + i][posY + j] == -1)
                         fld[posX + i][posY + j] = -2;
                }
            }
        ppos.pop_back();    
    }
}

Game::~Game()
{
}
