#ifndef LABEL_H
#define LABEL_H
#include "graphics.h"

class Label{
public:
        Label();
        ~Label();
        void setText(std::string text);
        void setPosition(int x, int y);
        void setColor(int bkcol, int col);
        void setSize(int sz);
        void setVisible(bool value);
        void draw();
private:
        char *caption;
        int x, y, bkcolor, color, size;
        bool visible;
};

#endif
