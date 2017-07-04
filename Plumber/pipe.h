#ifndef PIPE_H
#define PIPE_H

#include "graphics.h"
//bool type, if 0 - straight, 1 - curve
//size = 66x66
//direction, if 0 - up, 1 - right, 2 - dawn, 3 - right

class Pipe {
public:
        Pipe(bool typeOfFigure, int positionX, int positionY);   
        
        void setPosition(int x, int y);
        int getX();
        int getY();
        
        int getRelX();
        int getRelY();
        
        int getNode1X();
        int getNode1Y();
        int getNode2X();
        int getNode2Y();
        
        
        void setDirection(int dir);
        void setFilled(bool fld);
        void setRelPos(int x, int y);
        void rotate();
        void rotate(int count);
        
        void draw();
        
private:
    
        bool type;
        int direction;
        int x, y, node1X, node1Y, node2X, node2Y;
        int relX, relY;
        int size;
        bool filled;
};

#endif //PIPE_H
