#include "snake.h"
#include "screen.h"
#include <cstring>

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

void CSnake::paint()
{
    CFramedWindow::paint();

    if(pause) {
        gotoyx(geom.topleft.y + geom.size.y/2, geom.topleft.x + geom.size.x/2 - strlen("**** PAUSE ****")/2);
        printl("**** PAUSE ****");
        gotoyx(geom.topleft.y + geom.size.y/2 + 1, geom.topleft.x + geom.size.x/2 - strlen("p - continue")/2);
        printl("p - continue");
        return;
    }

    gotoyx(geom.topleft.y - 1, geom.topleft.x);
    printl("| LEVEL: %d |", level);

    if(help)
        paint_help();

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

    return CFramedWindow::handleEvent(c);
}

