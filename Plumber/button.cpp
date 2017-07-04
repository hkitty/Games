#include "button.h"
        
Button::Button(){
    focus = 0;
}

void Button::setCaption(std::string text){
    caption.setText(text);
}

void Button::setPosition(int x, int y){
    _x = x;
    _y = y;
    caption.setPosition(_x + 10, _y + 30);
}

void Button::setColor(int bkcolor, int textcolor){
    color = bkcolor;
    textColor = textcolor;
    caption.setColor(color, textColor);
}
        
void Button::draw(){
    if ( visible ) {
    setfillstyle(SOLID_FILL, color);
    bar(_x, _y, _x + 265, _y + 120);
    caption.draw();
        if(focus)
            rectangle(_x, _y, _x + 265, _y + 120);
        
    }
}

bool Button::isClick(int x, int y) 
{
    if ( x > _x && x < _x + 256 && y > _y && y < _y + 120 ) {
        return true;
    } else {
        return false;
    }
}
void Button::setFocus(bool focused)
{
    focus = focused;
}

void Button::setVisible(bool _visible)
{
    visible = _visible;
}

bool Button::getVisible()
{
    return visible;
}
