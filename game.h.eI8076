#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QEvent>
#include <QRGB>
#include <stdint.h>
#include <cstring>
#include "Fonts.h"
#include <math.h>
#include <QDateTime>

#include <QDebug>

#include "point2di.h"
#include "lib2d.h"

//Letter spacing for text printing functions
#define LetterSpace 1

//Frame rate of game
#define FrameRate   30

class Game{
public:
    //Game constructor
    Game(QImage *QI, int32_t XRs, int32_t YRs){
        pQI = QI; XRes = XRs; YRes = YRs;
    }

    //Game destructor
    ~Game(){
    }

    //Game functions
    void DrawGame(void);

    void DrawPix(uint32_t X, uint32_t Y, QRgb Col){
        if(X>=pQI->width()){
            //qDebug() << "X out of range: " << X;
            X = pQI->width()-1;
        }
        else if(Y>=pQI->height()){
            //qDebug() << "Y out of range: " << Y;
            Y = pQI->height()-1;
        }
        else{
            pQI->setPixel(X, Y, Col);
        }
    }

    int32_t XRes, YRes;

private:
    //Graphics buffer
    QImage *pQI;

};

#endif // GAME_H
