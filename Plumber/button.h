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
        void setVisible(bool _visible);
        
        bool getVisible();
        
        bool isClick(int x, int y);
                
private:
        Label caption;
        int _x, _y, color, textColor;
        bool focus;
        bool visible;
};

#endif
