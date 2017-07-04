#include "pipe.h"

Pipe::Pipe(bool typeOfFigure, int positionX, int positionY)
{
    size = 66;
    type = typeOfFigure;
    x = positionX;
    y = positionY;
    
    
    direction = rand()%4;
    
    filled = false;
    
    if(type)
    {
        switch(direction)
        {
            case 0:
                {
                    node1X = 1;
                    node1Y = 0;
                    
                    node2X = 0;
                    node2Y = -1;
                }
            break;
            
            case 1:
                {
                    node1X = 0;
                    node1Y = 1;
                    
                    node2X = 1;
                    node2Y = 0;
                }
            break;
            
            case 2:
                {
                    node1X = -1;
                    node1Y = 0;
                    
                    node2X = 0;
                    node2Y = 1;
                }
            break;
            
            case 3:
                {
                    node1X = -1;
                    node1Y = 0;
                    
                    node2X = 0;
                    node2Y = -1;
                }
            break;
        }
    }
    
    else
    {
        if(direction == 0 || direction == 2)
            {
                node1X = 0;
                node1Y = 1;
                
                node2X = 0;
                node2Y = -1;
            }
        else
            {
                node1X = 1;
                node1Y = 0;
                
                node2X = -1;
                node2Y = 0;
            }
    }
}   
        
void Pipe::setPosition(int positionX, int positionY)
{
    x = positionX;
    y = positionY;    
}

int Pipe::getX()
{
    return x;    
}

int Pipe::getY()
{
    return y;    
}
        
void Pipe::rotate()
{
    if(direction < 3)
        direction++;
    else direction = 0; 
    
    if(type)
    {
        switch(direction)
        {
            case 0:
                {
                    node1X = 1;
                    node1Y = 0;
                    
                    node2X = 0;
                    node2Y = -1;
                }
            break;
            
            case 1:
                {
                    node1X = 0;
                    node1Y = 1;
                    
                    node2X = 1;
                    node2Y = 0;
                }
            break;
            
            case 2:
                {
                    node1X = -1;
                    node1Y = 0;
                    
                    node2X = 0;
                    node2Y = 1;
                }
            break;
            
            case 3:
                {
                    node1X = -1;
                    node1Y = 0;
                    
                    node2X = 0;
                    node2Y = -1;
                }
            break;
        }
    }
    
    else
    {
        if(direction == 0 || direction == 2)
            {
                node1X = 0;
                node1Y = 1;
                
                node2X = 0;
                node2Y = -1;
            }
        else
            {
                node1X = 1;
                node1Y = 0;
                
                node2X = -1;
                node2Y = 0;
            }
    }   
}

void Pipe::rotate(int count)
{
    for(int i = 0; i < count; i++)
    {
        rotate();
    }    
}
        
void Pipe::draw()
{
    if(type) // if curve
    {
        switch(direction)
        {
            
            case 0:
                {
                    rectangle(x + 18, y + 1, x + 48, y + 8);
                    rectangle(x + 57, y + 18, x + 65, y + 48);
                    
                    line(x + 23,y + 8, x + 23, y + 43);
                    line(x + 23, y + 43, x + 57, y + 43);
                    line(x + 43, y + 8, x + 43, y + 23);
                    line(x + 43, y + 23, x + 57, y + 23);
                    
                    if(filled)
                    {
                        bar(x + 19, y + 2, x + 48, y + 8);
                        bar(x + 58, y + 19, x + 65, y + 48);
                        bar(x + 24, y + 10, x + 43, y + 43);
                        bar(x + 43, y + 24, x + 57, y + 43);
                    }
                }
            break;
            
            case 1:
                {
                    rectangle(x + 57, y + 18, x + 65, y + 48); 
                    rectangle(x + 18, y + 57, x + 48, y + 65);
                    
                    line(x + 23,y + 23, x + 57, y + 23);
                    line(x + 23, y + 23, x + 23, y + 57);
                    line(x + 43, y + 43, x + 57, y + 43);
                    line(x + 43, y + 43, x + 43, y + 57); 
                    
                    if(filled)
                    {
                        bar(x + 58, y + 19, x + 65, y + 48); 
                        bar(x + 19, y + 58, x + 48, y + 65);
                        bar(x + 43, y + 24, x + 57, y + 43);
                        bar(x + 24, y + 24, x + 43, y + 57);
                    }
                }
            break;
            
            case 2:
                {
                    rectangle(x + 18, y + 57, x + 48, y + 65);
                    rectangle(x + 1, y + 18, x + 8, y + 48);
                    
                    line(x + 43,y + 23, x + 8, y + 23);
                    line(x + 43, y + 23, x + 43, y + 57);
                    line(x + 23, y + 43, x + 23, y + 57);
                    line(x + 23, y + 43, x + 8, y + 43); 
                    
                    if(filled)
                    {
                        bar(x + 19, y + 58, x + 48, y + 65);
                        bar(x + 2, y + 19, x + 8, y + 48);
                        bar(x + 24, y + 24, x + 43, y + 57);
                        bar(x + 9, y + 24, x + 43, y + 43);
                    }
                }
            break;
            
            case 3:
                {
                    rectangle(x + 1, y + 18, x + 8, y + 48);
                    rectangle(x + 18, y + 1, x + 48, y + 8);
                    
                    line(x + 43,y + 43, x + 43, y + 8);
                    line(x + 43, y + 43, x + 8, y + 43);
                    line(x + 8, y + 23, x + 23, y + 23);
                    line(x + 23, y + 23, x + 23, y + 8); 
                    
                    if(filled)
                    {
                        bar(x + 19, y + 2, x + 48, y + 8);
                        bar(x + 2, y + 19, x + 8, y + 48);
                        bar(x + 24, y + 10, x + 43, y + 43);
                        bar(x + 9, y + 24, x + 43, y + 43);
                    }
                }
            break;
        }
    }
    
    else // if straight
    {
        if(direction == 0 || direction == 2)
        {
            rectangle(x + 18, y + 1, x + 48, y + 8);
            rectangle(x + 18, y + 57, x + 48, y + 65);
            rectangle(x + 23, y + 8, x + 43, y + 57);
            
            if(filled)
            {
                bar(x + 19, y + 2, x + 48, y + 8);
                bar(x + 19, y + 58, x + 48, y + 65);
                bar(x + 24, y + 9, x + 43, y + 57);
            }
        }
        
        else if (direction == 1 || direction == 3)
        {   
            rectangle(x + 1, y + 18, x + 8, y + 48);
            rectangle(x + 57, y + 18, x + 65, y + 48);
            rectangle(x + 8, y + 23, x + 57, y + 43);
            
            if(filled)
            {
                bar(x + 2, y + 19, x + 8, y + 48);
                bar(x + 58, y + 19, x + 65, y + 48);
                bar(x + 9, y + 24, x + 57, y + 43);
            }
        }    
    }
}

int Pipe::getNode1X()
{
    return relX + node1X;
}

int Pipe::getNode1Y()
{
    return relY + node1Y;
}

int Pipe::getNode2X()
{
    return relX + node2X;
}

int Pipe::getNode2Y()
{
    return relY + node2Y;
}

int Pipe::getRelX()
{
    return relX;
}

int Pipe::getRelY()
{
    return relY;
}

void Pipe::setRelPos(int x, int y)
{
    relX = x;
    relY = y;
}

void Pipe::setFilled(bool fld)
{
    filled = fld;
}

void Pipe::setDirection(int dir)
{
    direction = dir;
}
