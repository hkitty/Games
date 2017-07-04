#include "shape.h"

Shape::Shape(shapeClass type, int x, int y, int** field)
{
    _field = field;
    _x = x;
    _y = y;
    
    if(type == I)
    {
        sizeX = 1;
        sizeY = 4;
    }
    else if(type == O)
    {
        sizeX = 2;
        sizeY = 2;
    }
    else if(type == T)
    {
        sizeX = 3;
        sizeY = 2;
    }
    else if(type != I && type != O && type != T)
    {
        sizeX = 2;
        sizeY = 3;
    }
    
    shapeMatrix = new bool*[sizeX];
    
    for(int i = 0; i < sizeX; i++)
        shapeMatrix[i] = new bool[sizeY]; 
        
    for(int i = 0; i < sizeX; i++)
        for(int j = 0; j < sizeY; j++)
            shapeMatrix[i][j] = 0; 
    
    switch(type)
    {
        case I:
        {
            for(int i = 0; i < sizeY; i++)
                shapeMatrix[0][i] = 1;    
        }
            break;
            
        case L:
        {
            shapeMatrix[0][0] = 1;
            shapeMatrix[0][1] = 1;
            shapeMatrix[0][2] = 1;
            shapeMatrix[1][2] = 1;
        }
            break;
            
        case J:
        {
            shapeMatrix[1][0] = 1; 
            shapeMatrix[1][1] = 1;
            shapeMatrix[1][2] = 1;
            shapeMatrix[0][2] = 1;
        }
            break;
            
        case O:
        {
            shapeMatrix[0][0] = 1;
            shapeMatrix[0][1] = 1;
            shapeMatrix[1][0] = 1;
            shapeMatrix[1][1] = 1;
            
        }
            break;
            
        case T:
        {
            shapeMatrix[0][1] = 1;
            shapeMatrix[1][1] = 1;
            shapeMatrix[2][1] = 1;
            shapeMatrix[1][0] = 1;    
        }
            break;
            
        case Z:
        {
            shapeMatrix[1][0] = 1;
            shapeMatrix[1][1] = 1;
            shapeMatrix[0][1] = 1;
            shapeMatrix[0][2] = 1;
        }
            break;
            
        case S:
        {
            shapeMatrix[0][0] = 1;
            shapeMatrix[0][1] = 1;
            shapeMatrix[1][1] = 1;
            shapeMatrix[1][2] = 1;
        }
            break;
    }
    firstMatrix = shapeMatrix;
}

bool** Shape::getShape()
{
    return shapeMatrix;
}

int Shape::getX()
{
    return _x;
}

int Shape::getY()
{
    return _y;
}

void Shape::draw()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            _field[i][j] = 0;
    for(int i = 0; i < sizeX; i++)
        for(int j = 0; j < sizeY; j++)
            {
                _field[_x+i][_y+j] = shapeMatrix[i][j];
            }
}

int Shape::getSizeX()
{
    return sizeX;    
}

int Shape::getSizeY()
{
    return sizeY;    
}

void Shape::setPosition(int x, int y)
{
    _x = x;
    _y = y;
}

Shape::~Shape()
{
    for(int i = 0; i < sizeX; i++)
        delete[] shapeMatrix[i];
        
    delete [] shapeMatrix;
}

void Shape::rotate()
{   
    int tempX, tempY;
    
    bool** temp = shapeMatrix;
        
    tempX = sizeX;
    tempY = sizeY;
    sizeX = tempY;
    sizeY = tempX;
        
    shapeMatrix = new bool*[sizeX];
        
    for(int i = 0; i < sizeX; i++)
        shapeMatrix[i] = new bool[sizeY]; 
    
    for(int i = 0; i < sizeX; i++)
        for(int j = 0; j < sizeY; j++)
        {
            shapeMatrix[i][j] = temp[j][(sizeX-1) - i];    
        }
}

void Shape::setField(int** field)
{
    _field = field;
}
