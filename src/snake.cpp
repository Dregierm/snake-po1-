#include "snake.h"
#include "screen.h"
#include <cstring>
#include <cstdlib>
#include <ctime>

void CSnake::addFood()
{
    if((geom.size.x-2) * (geom.size.y-2) <= (int)snake.size()) return;
    CPoint temp;

    while (true)
    {
        temp = CPoint(rand() % (geom.size.x - 2) + 1, rand() % (geom.size.y - 2) + 1);
        for(auto &s: snake)
            if(!(s.x == temp.x && s.y == temp.y)) {
                food = temp;
                return;
            }
    }
}

void CSnake::reset()
{
    alive = true;
    help = pause = false;
    level = 0;
    snake.clear();

    snake.push_back(CPoint(4, 2)); //head *
    snake.push_back(CPoint(3, 2)); //tail
    snake.push_back(CPoint(2, 2)); //tail
    addFood();
}

void CSnake::paint_snake()
{
    gotoyx(snake[0].y + geom.topleft.y, snake[0].x + geom.topleft.x);
    printc('*');

    for (unsigned int i = 1; i < snake.size(); i++) {
        gotoyx(snake[i].y + geom.topleft.y, snake[i].x + geom.topleft.x);
        printc('+');
    }
}

void CSnake::paint_help()
{
    int  y = geom.topleft.y + 4, x = geom.topleft.x + 3;
    gotoyx(y++, x);
    printl("h - toggle help information");
    gotoyx(y++, x);
    printl("p - toggle pause/play mode");
    gotoyx(y++, x);
    printl("r - restart game");
    gotoyx(y++, x); x+=9;
    printl("arrows - move snake (in play mode) or");
    gotoyx(y, x);
    printl("move window (in pause mode)");
}

CSnake::CSnake(CRect r, char _c): CFramedWindow(r, _c)
{
    srand(time(NULL));
    reset();
    help = true;
}

void CSnake::paint()
{
    CFramedWindow::paint();

    if(help)
        paint_help();

    if(!alive) {
        gotoyx(geom.topleft.y + 1, geom.topleft.x + 1);
        printl("GAME OVER, result: %d", level);
        return;
    }

    if(pause) {
        gotoyx(geom.topleft.y + geom.size.y/2, geom.topleft.x + geom.size.x/2 - strlen("**** PAUSE ****")/2);
        printl("**** PAUSE ****");
        gotoyx(geom.topleft.y + geom.size.y/2 + 1, geom.topleft.x + geom.size.x/2 - strlen("p - continue")/2);
        printl("p - continue");
        return;
    }

    gotoyx(geom.topleft.y - 1, geom.topleft.x);
    printl("| LEVEL: %d |", level);

    paint_snake();

    gotoyx(food.y + geom.topleft.y, food.x + geom.topleft.x);
    printc('O');
}

bool CSnake::handleEvent(int c)
{
    if( tolower(c) == 'p' ) {
        pause = !pause;
        return true;
    }

    if( tolower(c) == 'h' ) {
        help = !help;
        return true;
    }

   /* if(!pause) {
        switch (key) {
            case KEY_UP:
        }
    }*/

    return CFramedWindow::handleEvent(c);
}

