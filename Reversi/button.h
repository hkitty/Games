#ifndef BUTTON_H
#define BUTTON_H

#include "graphics.h"
#include "label.h"

class Button{
public:
        Button();
        void setCaption(std::string text);
        void setPosition(int x, int y);
        void setColor(int bkcolor, int textcolor);
        void draw();
        void setFocus(bool focused);
                
private:
        Label caption;
        int _x, _y, color, textColor;
        bool focus;
};

#endif
