#include "shape.h"
#include <cmath>
#include <iostream>

Shape::Shape(int type, int x, int y, int** field)
{
    double a, b, xx, yy;
    a = x/52;
    b = y/52;
    
    _type = type;
    _field = field;

    std::modf(a, &xx);
    std::modf(b, &yy);
    std::cout << "Position: " << a << ":" << b << std::endl;
    

    _x = (int)xx;
    _y = (int)yy;
    
    positionX = _x - 1;
    positionY = _y - 1;

    _x = _x * 52 + 15;
    _y = _y * 52 + 15;
    
    if (_type == 1) {
        _color == BLACK;
    }
    if (_type == -1) {
        _color = WHITE;
    }
    
    std::cout << "Color: " << _color;
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

int Shape::getPosX()
{
    return positionX;
}

int Shape::getPosY()
{
    return positionY;    
}

void Shape::draw()
{
    _field[positionX][positionY] = _type;
}

void Shape::setPosition(int x, int y)
{
    _x = x;
    _y = y;
}

Shape::~Shape()
{

}
