#ifndef SHIP_H
#define SHIP_H

#include "vector"

class Ship{

public:
        Ship(int** fld, int sz);
    
        void setCoordinates(int _x, int _y);
        int getX();
        int getY();
       
        bool draw();
       
        bool check(int _x, int _y);
        void rotate();
        void setSize(int sz);
        void setField(int **fld, int mSize);
       
private:
        int** field;
        int matrixSize;
        int size;
        int x,y;
        bool dir;      
      
};

#endif
