#ifndef GAME_H
#define GAME_H

#include "button.h"
#include "label.h"
#include "graphics.h"
#include "iostream"
#include "vector"
#include "pipe.h"
#include "time.h"
#include "cmath"
#include <string>
#include "sstream"
        
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
    
    void checkWay();
    
    void initPipes();
    
    void drawDecor();
    
    Pipe* pipe;
    
    std::vector<Pipe*> pipes;
    
    bool exit;
    bool game;
    
    bool filled;
    
    bool** level1;
    
    struct tm gameTime;
    time_t startTime, currTime;
    double passedTime;

    Button *exitBtn;
    Label *winLabel, *timeToEnd;
};

#endif // GAME_H
