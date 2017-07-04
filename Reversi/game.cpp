#include "game.h"

#define BL  1
#define NN  0
#define WH  -1

Game::Game()
{
initwindow(640,480,"Reversi",100,100,true,true);

gameOver = false;
current = BL;


win.setPosition(500, 100);
win.setColor(WHITE, 5);

win.setVisible(false);


text.setText("Current move");
text.setPosition(500, 300);
text.setColor(GREEN, 1);
text.setVisible(true);

scorew.setText("White: 2");
scorew.setPosition(500, 150);
scorew.setColor(GREEN, 1);
scorew.setVisible(true);

scoreb.setText("Black: 2");
scoreb.setPosition(500, 200);
scoreb.setColor(GREEN, 1);
scoreb.setVisible(true);


playerInputWait = true;


// ================================Создаем пустое поле====================================
int i = 0;
int j = 0;

field = new int* [8];
for(int count = 0; count < 8; count++) {
    field[count] = new int[8];
}       
    
for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
        field[i][j] = 0;     
    }
}
// ========================Выставляем 4 фишки на стартовые позиции=======================
field[3][3] = WH;
field[3][4] = BL;
field[4][4] = WH;
field[4][3] = BL;
}
// ======================================================================================


int Game::start()
{
    exit = false;
    status = 1;
    
    settextstyle(0,HORIZ_DIR,10);
    
    while(!exit)
    {
        delay(100);
        processEvents(); //Взаимодействие с пользователем

        render(); //Отрисовка
    }
    closegraph();
    return status;
}

void Game::processEvents()
{
        
    if(ismouseclick(WM_LBUTTONDOWN) && !gameOver)
    {
        getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

            if ( mouseX > 40 && mouseX < 456 && mouseY > 40 && mouseY < 456 ) {
                
                Shape* temp;

                temp = new Shape(current, mouseX, mouseY, field);
                int i = temp->getPosX();
                int j = temp->getPosY();
                if (i >= 0 && i <= 7 && j >= 0 && j <= 7) {
                    if (field[i][j] == 0) {
                        
                        bool isok = reverse(temp);
                        
                        if ( isok ) {
                            shape = temp;
                            playerInputWait = false;
                            current = -current;
                        } else {
                            field[i][j] == 0;
                        }
                    } else {}
                }
            } else {
                current = -current;
            }
    } 
    
    if(kbhit())
    {      
        char key = getch();
        if(key == 27)
        {
            exit = true;
            status = 0;
        }
    }
}

void Game::score() 
{
    int w = 0;
    int b = 0;
    
    for( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            if ( field[i][j] == 1) {
                b++;
            } else if ( field[i][j] == -1 ){
                w++;
            } else {  }
        }
    }
    char ww[3];
    itoa(w,ww,10);
    std::string www = "White: ";
    www += ww;
    
    scorew.setText(www);
    
    char bb[3];
    itoa(b,bb,10);
    std::string bbb = "Black: ";
    bbb += bb;
    
    scoreb.setText(bbb);
    
    if ( w + b == 64 ) {
        if ( w > b ) {
            win.setText("WHITE win!");
            win.setVisible(true);
        }
        if ( w < b ) {
            win.setText("BLACK win!");
            win.setVisible(true);
        }
        if ( w == b ) {
            win.setText("TIE!");
            win.setVisible(true);
        }
        gameOver = true;
    }
    
}

void Game::currentMove(int _color)
{
    if (_color == 1) {
        setfillstyle(SOLID_FILL, BLACK);
    }
    if (_color == -1) {
        setfillstyle(SOLID_FILL, WHITE);
    }
    fillellipse(550, 350, 25, 25);
}

void Game::render()
{
    score();
    setfillstyle(SOLID_FILL, GREEN);
    bar(0,0,getmaxx(),getmaxy());
    
    settextstyle(0,HORIZ_DIR,0);
    text.draw();
    scorew.draw();
    scoreb.draw();
    win.draw();
    
    setfillstyle(SOLID_FILL, BROWN);
    bar(40,40,458,458);

    
    if(!playerInputWait) {
        shape -> draw();
    }
    
    setcolor(WHITE);
    for(int i = 0; i <= 8; i++)
        {
            line(40 + i*52, 40,40 + i*52, 456);
        }
    
    for(int i = 0; i <= 8; i++)
        {
            line(40,40 + i*52,456,40 + i*52);
        }

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            if(field[i][j] == 1)
            {
                setfillstyle(SOLID_FILL, BLACK);
                fillellipse(66 + i * 52, 66 + j * 52, 25, 25);
            } else if (field[i][j] == -1) {
                setfillstyle(SOLID_FILL, WHITE);
                fillellipse(66 + i * 52, 66 + j * 52, 25, 25);
            }
        }
    }
    currentMove(current);
    
        
    settextstyle(0,HORIZ_DIR,20);   
    swapbuffers();
}

int Game::isReversible(const int m, const int n)
{
    
}

bool Game::reverse(Shape *temp)
{
    bool isOk = false;
    int x = temp -> getPosX();
    int y = temp -> getPosY();

    if ( y <= 1 ) {

        isOk = toBot(x, y);
        
        if ( x <= 1 ) {
            if ( toRight(x, y) ) {
                isOk = true;
            } if ( toBotRight(x, y) ) {
                isOk = true;
            }
        } 
        
        if ( x >= 6 ){
            if ( toLeft(x, y) ) {
                isOk = true;
            } if ( toBotLeft(x, y) ) {
                isOk = true;
            }
            
        } 
        
        if ( x > 1 && x < 6 ) {
            if ( toBotLeft(x, y) ) {
                isOk = true;
            } if ( toBotRight(x, y) ) {
                isOk = true;
            } if ( toRight(x, y) ) {
                isOk = true;
            } if ( toLeft(x, y) ) { 
                isOk = true;
            }
        }
    }
    
    if ( y >= 6 ) {
        isOk = toTop(x, y);
        
        if ( x <= 1 ) {
            if ( toRight(x, y) ) {
                isOk = true;
            } if ( toTopRight(x, y) ) {
                isOk = true;
            }
        } 
        
        if ( x >= 6 ){
            if ( toLeft(x, y) ) {
                isOk = true;
            } if ( toTopLeft(x, y) ) {
                isOk = true;
            }
            
        } 
        
        if ( x > 1 && x < 6 ) {
            if ( toTopLeft(x, y) ) {
                isOk = true;
            } if ( toTopRight(x, y) ) {
                isOk = true;
            } if ( toRight(x, y) ) {
                isOk = true;
            } if ( toLeft(x, y) ) { 
                isOk = true;
            }
        }
    }
    
    if ( y > 1 && y < 6 ) {
        if ( toTop(x, y) ) {
            isOk = true;
        } 
        if ( toBot(x, y) ) {
            isOk = true;
        }
        
        if ( x <= 1 ) {
            if ( toRight(x, y) ) {
                isOk = true;
            } if ( toTopRight(x, y) ) {
                isOk = true;
            } if ( toBotRight(x, y) ) {
                isOk = true;
            }
        } 
        
        if ( x >= 6 ) {
            if ( toLeft(x, y) ) {
                isOk = true;
            } if ( toTopLeft(x, y) ) {
                isOk = true;
            } if ( toBotLeft(x, y) ) {
                isOk = true;
            }
        }
        
        if ( x > 1 && x < 6 ) {
            if ( toLeft(x, y) ) {
                isOk = true;
            } if ( toRight(x, y) ) {
                isOk = true;
            } if ( toTopLeft(x, y) ) {
                isOk = true;
            } if ( toTopRight(x, y) ) {
                isOk = true;
            } if ( toBotRight(x, y) ) {
                isOk = true;
            } if ( toBotLeft(x, y) ) {
                isOk = true;
            }
        }
    }
    
    return isOk;
}

bool Game::toRight(int x, int y) {
    bool isOk = false;
    int i = x+1;
    int j = y;
    
    if ( field[x+1][y] == -current ) {
        while ( field[i][j] == -current ) {
            if ( i < 7 ) {
                if ( field[i+1][j] == current ) { 
                    for ( i; i > x ; i-- ) {
                        field[i][j] = current;
                        isOk = true;
                    }
                } else {  }
            } else { break; }
            i++;
        }
    }
        
    return isOk;
}

bool Game::toLeft(int x, int y) {
    bool isOk = false;
    int i = x - 1;
    int j = y;

        if ( field[x-1][y] == -current ) {
            while ( field[i][j] == -current) {
                if ( i > 0 ) {
                    if ( field[i-1][j] == current ) { 
                        for ( i; i < x ; i++ ) {
                            field[i][j] = current;
                            isOk = true;
                        }
                    } else {  }
                } else { break;}
                i--;
            }
        }

    return isOk;
}
    
bool Game::toBot(int x, int y) {
    bool isOk = false;
    int i = x;
    int j = y + 1;

        if ( field[x][y+1] == -current ) {
            while ( field[i][j] == -current ) {
                if ( j < 7 ) { 
                    if ( field[i][j+1] == current ) { 
                        for ( j; j > y ; j-- ) {
                            field[i][j] = current;
                            isOk = true;
                        }
                    } else {  }
                } else { break;}
                j++;
            }
        }
    
    return isOk;
}

bool Game::toTop(int x, int y) {
    bool isOk = false;
    int i = x;
    int j = y - 1;
        if ( field[x][y-1] == -current ) {
            while ( field[i][j] == -current ) {
                if ( j > 0 ) {
                    if ( field[i][j-1] == current ) { 
                        for ( j; j < y ; j++ ) {
                            field[i][j] = current;
                            isOk = true;
                        }
                    } else {  }
                } else { break;}
                j--;
            }
        }
    
    return isOk;
}

bool Game::toBotRight(int x, int y) {
    bool isOk = false;
    int i = x + 1;
    int j = y + 1;

        if ( field[x+1][y+1] == -current) {
            while ( field[i][j] == -current ) {
                if ( i < 7 && j < 7 ) {
                    if ( field[i+1][j+1] == current ) {
                        for (i, j; i > x, j > y; i--, j--) {
                            field[i][j] = current;
                            isOk = true;
                        }
                    } else {  } 
                } else { break;}
                i++;
                j++;
            }
        }
    
    return isOk;
}

bool Game::toTopLeft(int x, int y) {
    bool isOk = false;
    int i = x - 1;
    int j = y - 1;

    if ( field[x-1][y-1] == -current ) {
        while ( field[i][j] == -current ) {
            if ( i > 0 && j > 0 ) {
                if ( field[i-1][j-1] == current ) {
                    for (i, j; i < x, j < y; i++, j++) {
                        field[i][j] = current;
                        isOk = true;
                    }
                } else {  } 
            } else { break;}
            i--;
            j--;
        }
    }
    
    return isOk;
}

bool Game::toBotLeft(int x, int y) {
    bool isOk = false;
    int i = x - 1;
    int j = y + 1;  

        if ( field[x-1][y+1] == -current ) {
            while ( field[i][j] == -current ) {
                if (i > 0 && j < 7) {
                    if ( field[i-1][j+1] == current ) {
                        for (i, j; i < x, j > y; i++, j--) {
                            field[i][j] = current;
                            isOk = true;
                        }
                    } else {  } 
                } else { break;}
                i--;
                j++;
            }
        }
    
    return isOk;
}

bool Game::toTopRight(int x, int y) {
    bool isOk = false;
    int i = x + 1;
    int j = y - 1;

        if ( field[x+1][y-1] == -current ) {
            while ( field[i][j] == -current ) {
                if ( i < 7 && j > 0 ) {
                    if ( field[i+1][j-1] == current ) {
                        for (i, j; i > x, j < y; i--, j++) {
                            field[i][j] = current;
                            isOk = true;
                        }
                    } else {  } 
                } else { break;}
                i++;
                j--;
            }
        }
        
    return isOk;
}

Game::~Game()
{

}
