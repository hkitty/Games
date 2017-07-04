#ifndef GAME_H
#define GAME_H

#include "button.h"
#include "label.h"
#include "graphics.h"
#include "iostream"
#include "vector"
#include "ship.h"
#include "cmath"
#include <string>

    struct pos{
        int x;
        int y;
        };
        
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
    void initAIField();
    bool checkIfDead(int _x, int _y, int** fld);
    
    bool shoot(int _x, int _y, int** fld);
    
    int** playerField;
    int** AIField;
    
    Ship* ship;
    std::vector<int> ships;
    
    int **matrix;
    int SIZE;
    
    bool waitForPlayer;
    bool playerWin;
    bool AIWin;
    bool status;
    bool exit;
    
    Label *label, *republic, *republic2, *l1, *info, *stat, *esc;
};

#endif // GAME_H
