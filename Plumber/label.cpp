#include "label.h"

Label::Label(){
    setColor(0, 0);
    setText("Default");
    setPosition(100,100); 
    setSize(1);   
    visible = true;
}

void Label::draw(){
    if(visible)
    {
        //setusercharsize(size,1,size,1);
        //settextstyle(0,HORIZ_DIR,0);
        setcolor(color);
        outtextxy(x, y, caption); 
    }   
}

void Label::setColor(int bkcol, int col){
    bkcolor = bkcol;
    color = col;
}

void Label::setText(std::string text){
    caption = new char[text.length() + 1];
    std::strcpy(caption, text.c_str()); 
}

void Label::setPosition(int _x, int _y){
    x = _x;
    y = _y;
}

void Label::setSize(int sz){
    size = sz;
}

Label::~Label(){
    delete[] caption;
}

void Label::setVisible(bool val){
    if(!val)
    {
        visible = false;
    }
    else
    {
        visible = true;  
    }
}
