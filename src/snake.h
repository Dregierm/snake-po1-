#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"

class CSnake:public CFramedWindow
{
private:
    int level = 0;
    bool pause = false;
    bool help = true;

    void paint_help();
public:
    CSnake(CRect r, char _c = ' '): CFramedWindow(r, _c) {};

    void paint();
    bool handleEvent(int c);
};

#endif
