#ifndef SHAPE_H
#define SHAPE_H

#include "graphics.h"

class Shape{

public:
        Shape(int type, int _x, int _y, int** field);
        ~Shape();
        bool** getShape();
        int getX();
        int getY();
        int getPosX();
        int getPosY();
        void setPosition(int x, int y);
        
        void draw();
        
private:
        int positionX;
        int positionY;
        
        int _type;
        int _color;
        int** _field;
        bool** shapeMatrix;
        int _x, _y;
};

#endif
