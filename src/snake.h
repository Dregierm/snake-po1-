#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include <iostream>
#include <vector>

class CSnake:public CFramedWindow
{
private:
    int level;
    bool pause;
    bool help;
    bool alive;

    CPoint food;
    std::vector <CPoint> snake;

    void reset();
    void paint_help();
    void paint_snake();
    void addFood();
public:
    CSnake(CRect r, char _c = ' ');

    void paint();
    bool handleEvent(int c);
};

#endif
