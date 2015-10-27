#include "game.h"

extern bool Mouse, Keys[];
extern uint32_t MouseXP, MouseYP;
extern uint32_t MouseXR, MouseYR;

void Game::DrawGame(void){
    static lib2d L2(this);
    Point2DI P(100, 100);

    pQI->fill(Qt::white);
    L2.PStr("Hello!", P, 0, qRgb(0,0,0), qRgb(255,255,255));
}
