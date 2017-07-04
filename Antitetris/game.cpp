#include "game.h"

Game::Game()
{
initwindow(640,480,"Play AntiTetris",100,100,true,true);

gameOver = false;

score = 0;

text.setText("Нажмите Esc для выхода. Для выбора типа");
text.setPosition(250, 20);
text.setColor(3,1);
text.setVisible(true);
text2.setText("фигуры используйте клавиши от 1 до 7.");
text2.setPosition(250, 40);
text2.setColor(3,1);
text2.setVisible(true);
text3.setText("Пробел - поворот, Enter - подтвердить.");
text3.setPosition(250, 60);
text3.setColor(3,1);
text3.setVisible(true);


over.setText("Игра окончена!");
over2.setText("Нажмите Esc для выхода");
over.setPosition(30,200);
over2.setPosition(200,300);
over.setColor(WHITE,BLACK);
over2.setColor(WHITE,BLACK);
over.setVisible(false);
over2.setVisible(false);

scoreLabel.setText("Счет: 0");
scoreLabel.setPosition(400,400);
scoreLabel.setColor(3,1);
playerInputWait = true;

int i = 0;
int j = 0;

field = new int* [10];
exampleField = new int* [4];

for(int count = 0; count < 10; count++)
    {
        field[count] = new int[20];
    }  

for(int count = 0; count < 4; count++)
    {
        exampleField[count] = new int[4];
    }  
    
for(int i = 0; i < 10; i++)
    for(int j = 0; j < 20; j++)
        field[i][j] = 0;   
        
for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
        exampleField[i][j] = 0;  
}

int Game::start()
{
    exit = false;
    status = 1;
    
    int frames = 50000, i = 0;
    settextstyle(0,HORIZ_DIR,10);
    
    while(!exit)
    {
        delay(100);
        processEvents();
        update();
        render(); 

    }
    closegraph();
    return status;
}

void Game::processEvents()
{
    if(kbhit())
    {      
        char key = getch();
        if(key == 27)
        {
            exit = true;
            status = 0;
        }
           
        if(playerInputWait && key < 56 && key > 48 && !gameOver)
        {
        Shape* temp;
        
            if(key == 49) // Клавиша 1
                    temp = new Shape(I,0,0, exampleField);

            if(key == 50) // Клавиша 2
                    temp = new Shape(L,0,0, exampleField);
                    
            if(key == 51) // Клавиша 3
                    temp = new Shape(J,0,0, exampleField);
                
            if(key == 52) // Клавиша 4
                    temp = new Shape(O,0,0, exampleField);
                
            if(key == 53) // Клавиша 5
                    temp = new Shape(T,0,0, exampleField);
            
            if(key == 54) // Клавиша 6
                    temp = new Shape(Z,0,0, exampleField);
            
            if(key == 55) // Клавиша 7
                    temp = new Shape(S,0,0, exampleField);
                    
        temp->draw();            
        shape = temp;
        }
        
        if(key == ' ')
            {
                shape->rotate();
                shape->draw();
            }
        if(key == '\r')
            {
                playerInputWait = false;
            }
    }
}

void Game::render()
{
    setfillstyle(SOLID_FILL, CYAN);
    bar(0,0,getmaxx(),getmaxy());
    
    settextstyle(0,HORIZ_DIR,0);
    text.draw();
    text2.draw();
    text3.draw();
    scoreLabel.draw();
    
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(20,20,240,460);
    bar(500,280,589,369);
    
    setcolor(DARKGRAY);
    for(int i = 0; i <= 10; i++)
        {
            line(20 + i*22, 20,20 + i*22, 460);
        }
    
    for(int i = 0; i <= 20; i++)
        {
            line(20,20 + i*22,240,20 + i*22);
        }   
        
    for(int i = 0; i <= 4; i++)
        {
            line(500 + i*22, 280,500 + i*22, 369);
        }
    
    for(int i = 0; i <= 4; i++)
        {
            line(500,280 + i*22,589,280 + i*22);
        }       
    
    setfillstyle(SOLID_FILL, BLACK);
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 20; j++)
        {
            if(field[i][j] == 2)
            {
                bar(22 + i*22, 22 + j*22, 21 + i*22 + 20, 21 + j*22 + 20);
            }
        }
        
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            if(exampleField[i][j] == 1)
            {
                bar(502 + i*22, 282 + j*22, 501 + i*22 + 20, 281 + j*22 + 20);
            }
        }
    setcolor(BLUE);
    settextstyle(2,HORIZ_DIR,10);
    drawFigures(300,150);
        
    settextstyle(0,HORIZ_DIR,20);
    over.draw();  
    
    settextstyle(0,HORIZ_DIR,1);
    over2.draw();  
    swapbuffers();
}

void Game::update()
{       
    for(int i = 0; i < 10; i++) //Проверка на переполнение стакана ------------
    {
        if(field[i][0] == 2)
        {
            over.setVisible(true);
            over2.setVisible(true);
            gameOver = true;
        } 
    }  
    //-------------------------------------------------------------------------
    
if(!gameOver)
    { 
    bool line = false;
    int lineIndex = 0;
    int count = 0;
    
    for(int j = 0; j < 20; j++) //Проверка на сложение линий из 10
    {
        for(int i = 0; i < 10; i++)
        {
            if(field[i][j] == 2)
                     count++;
    
            if(count == 10)
            {
                lineIndex = j;
                line = true;
                score++;
                char str[3];
                itoa(score,str,10);
                std::string str2 = "Счет: ";
                str2 += str;
                scoreLabel.setText(str2);
            }
        }
    count = 0;
    }
    
    if(line)
    {
        int** temporary = field;
        for(int i = 19, n = 19; i >0; i--, n--)
            for(int j = 9; j >= 0; j--)
            {   
                if(n == lineIndex)
                    n--;
                    
                field[j][i] = temporary[j][n];
            }
        
        for(int i = 0; i < 10; i++)
            field[i][0] = 0;
    }       
     
    //-------------------------------------------------------------------------
    
    if(!playerInputWait) //Если игрок уже выбрал фигуру ставим ее в подходящее место
    {
        bool flag = true;  
        bool** matrix = shape->getShape();
        int x = shape->getSizeX();
        int y = shape->getSizeY();
        int If = 19 , Jf = 0;
        int rotateCount;
        
        int positionX = 0;
        int positionY = 19;
        
        for(int n = 0; n < 4; n++)
        {
            shape->rotate();
            for(If; If >=0; If--) //Ищем подходящее место
            {
                for(Jf = 0; Jf < 10 - (x-1); Jf ++)
                {
                    for(int i = 0; i < x; i++)
                        for(int j = 0; j < y; j++)
                        {
                            if(field[Jf + i][If - j] == 2 && matrix[i][(y-1)-j] == 1)
                                flag = false;
                        }
                    
                    if(flag)
                    {
                        for(int i = 0; i < x; i++)
                            for(int j = If-(y-1); j > y-1; j--)
                                if(field[Jf+i][j] == 2)
                                    flag = false;
                    }
                    
                    if(flag) //Ставим, если нашли
                    {
                        if(n==0)
                        {
                            positionX = Jf;
                            positionY = If;
                            rotateCount = n;
                        }
                        
                        if(positionY < If && n > 0)
                        {
                            positionX = Jf;
                            positionY = If; 
                            rotateCount = n;
                        } 
                        
                        if(If >= positionY)
                        {
                            If = 0;
                            Jf = 10 - (x-1);  
                        }           
                    }
                    else
                    {
                        flag = true;
                    }
                }         
            }
        }
        
        for(int n = 0; n < rotateCount; n++)
            shape->rotate();
            
        for(int i = 0; i < x; i++)
            for(int j = 0; j < y; j++)
                {
                    if(matrix[i][(y-1)-j] == 1)
                        field[positionX + i][positionY - j] = 2;
                } 
                
        playerInputWait = true;              
    }   
    //-------------------------------------------------------------------------
    
    if(playerInputWait)
    {
        for(int i = 0; i < 10; i++)
            for(int j = 0; j < 20; j++)
                if(field[i][j] != 2)
                    field[i][j] = 0;
    }
    
    }
}

Game::~Game()
{
}

void Game::drawFigures(int x, int y)
{
    int startX = x;
    int startY = y;
    int tX = x;
    int tY = y;
    
    outtextxy(x,y-40,"1");
    // I
    bar(x, y, x+20, y+20);
    y+=22;    
    bar(x, y, x+20, y+20); 
    y+=22;
    bar(x, y, x+20, y+20); 
    y+=22;
    bar(x, y, x+20, y+20);
    
    tX+=44;
    x = tX;
    y = tY;
    
    outtextxy(x+6,y-40,"2");
    //L
    bar(x, y, x+20, y+20);
    y+=22;     
    bar(x, y, x+20, y+20);
    y+=22;
    bar(x, y, x+20, y+20);
    x+=22;
    bar(x, y, x+20, y+20);
    
    tX+=88;
    x = tX;
    y = tY;

    outtextxy(x-11,y-40,"3");    
    //J
    bar(x, y, x+20, y+20);
    y+=22;     
    bar(x, y, x+20, y+20);
    y+=22;
    bar(x, y, x+20, y+20);
    x-=22;
    bar(x, y, x+20, y+20);
    
    tX+=44;
    x = tX;
    y = tY;
    
    outtextxy(x+11,y-40,"4");
    //O
    bar(x, y, x+20, y+20);
    y+=22;     
    bar(x, y, x+20, y+20);
    x+=22;
    bar(x, y, x+20, y+20);
    y-=22;
    bar(x, y, x+20, y+20);
    
    tX+=66;
    x = tX;
    y = tY;
    
    outtextxy(x+11,y-40,"5");
    //T
    bar(x, y, x+20, y+20);
    y+=22;     
    bar(x, y, x+20, y+20);
    x+=22;
    bar(x, y, x+20, y+20);
    y+=22;
    x-=22;
    bar(x, y, x+20, y+20);
    
    tX = startX + 22;
    tY+=144;
    x = tX;
    y = tY;

    outtextxy(x-11,y-40,"6");
    //Z
    bar(x, y, x+20, y+20);
    y+=22;     
    bar(x, y, x+20, y+20);
    x-=22;
    bar(x, y, x+20, y+20);
    y+=22;
    bar(x, y, x+20, y+20);
    
    tX += 44;
    x = tX;
    y = tY;
    
    outtextxy(x+11,y-40,"7");
    //S
    bar(x, y, x+20, y+20);
    y+=22;     
    bar(x, y, x+20, y+20);
    x+=22;
    bar(x, y, x+20, y+20);
    y+=22;
    bar(x, y, x+20, y+20);
    
}
