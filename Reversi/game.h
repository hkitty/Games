#ifndef GAME_H
#define GAME_H
#include "button.h"
#include "label.h"
#include "shape.h"
#include "label.h"
#include <string>
#include "graphics.h"
#include "iostream"
#include "vector"
#include <list>

class Game
{
public:
    Game();
    ~Game();
    int start();

private:
    void processEvents();
    void render();
    void currentMove(int _color);
    
    bool toRight(int x, int y);
    bool toLeft(int x, int y);
    
    bool toBot(int x, int y);
    bool toTop(int x, int y);
    
    bool toBotRight(int x, int y);
    bool toTopLeft(int x, int y);
    bool toBotLeft(int x, int y);
    bool toTopRight(int x, int y);
    
    bool reverse(Shape *temp);
    void score();
    int isReversible(const int m, const int n);
    
    bool exit, gameOver;
    bool playerInputWait;
    int status;
    int current;
    int mouseX, mouseY;
    Button exitBtn;
    Label text, text2, scorew, scoreb, win;
    
    Shape* shape;
    int** field;
};

#endif // GAME_H
