#include "ship.h"

Ship::Ship(int** fld, int sz)
{
    size = sz;
    field = fld;   
    dir = false;
}

void Ship::setCoordinates(int _x, int _y)
{
    x = _x;
    y = _y; 
}

int Ship::getX()
{
    return x;
}

int Ship::getY()
{
    return y;
}
       
bool Ship::draw()
{  
    if(dir)  
    {
        if(y + size - 1 < 10)
        {
            bool checked = true;
            
            for(int j = 0; j < size; j++) {
                if(!check(x,y+j))
                   checked = false; 
            }
            
            if(!checked)
                return false;
            
            for(int j = 0; j < size; j++) {
                field[x][y+j] = 1;
            }
            
            return true;
        }
    }
    
    else
    {
        if(x + size - 1 < 10)
        {
            bool checked = true;
            
            for(int j = 0; j < size; j++) {
                if(!check(x+j,y))
                   checked = false; 
            }
            
            if(!checked)
                return false;
                
            for(int j = 0; j < size; j++) {
                field[x+j][y] = 1; 
            }
            
            return true;   
        }
    }
    return false;
}

void Ship::setSize(int sz)
{
    size = sz;
}

void Ship::setField(int **fld, int mSize) 
{
    field = fld;
    matrixSize = mSize;
}

void Ship::rotate()
{
    dir = !dir;
}

bool Ship::check(int _x, int _y)
{
    bool checked = true;
    int posX, posY;
    posX = _x-1;
    posY = _y-1;
    
    for(int i = 0; i < 3; i++) 
        for(int j = 0; j < 3; j++)
        {
            if(posX + i < 0 || posY + j < 0 || posX + i > matrixSize-1 || posY + j > matrixSize-1)
            {
 
            }
            else 
            {
                if(field[posX + i][posY + j] == 1)  
                    checked = false; 
            }
        }
        
    return checked;
}
