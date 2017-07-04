#ifndef GAME_H
#define GAME_H
#include "button.h"
#include "label.h"
#include "shape.h"
#include "label.h"
#include "graphics.h"
#include "iostream"
#include "vector"

class Game
{
public:
    Game();
    ~Game();
    int start();

private:
    void processEvents();
    void render();
    void update();
    void drawShape(shapeClass type, int x, int y);
    void drawFigures(int x, int y);
    
    bool exit, gameOver;
    bool playerInputWait;
    int status, score;
    Button exitBtn;
    Label scoreLabel;
    Label text, text2, text3, text4;
    Label over, over2;
    Shape* shape;
    
    int** field;
    int** exampleField;
};

#endif // GAME_H
