#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"
#include <stdint.h>
#include <QDateTime>
#include <QTimer>
#include <QRGB>
#include <QDebug>
#include <QKeyEvent>

QImage *QI;
QTimer Timer;

Game *G;

//Key press array
#define AMNT_KEYS   64
bool Keys[AMNT_KEYS] = {false};

bool Mouse = false;
uint32_t MouseXP, MouseYP;
uint32_t MouseXR, MouseYR;

uint32_t FCnt = 0;

void DrawScreen(void);

MainWindow::MainWindow(QWidget *Parent) :
    QMainWindow(Parent),
    ui(new Ui::MainWindow)
{

    QDateTime T;
    ui->setupUi(this);

    //Initialize Game engine
    qDebug() << ui->label->width() << "x" << ui->label->height();
    QI = new QImage(ui->label->width(), ui->label->height(), QImage::Format_RGB888);
    G = new Game(QI, ui->label->width(), ui->label->height());


    //Seed for random number generator
    qsrand(T.currentMSecsSinceEpoch());

    //Frame rate timer
    connect(&Timer, SIGNAL(timeout()), this, SLOT(DrawScreen()));
    Timer.start((1000/FrameRate));
}

void MainWindow::DrawScreen(void){
    G->DrawGame();
    FCnt++;

    ui->label->setPixmap(QPixmap::fromImage(*QI));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::event(QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *KEvent = static_cast<QKeyEvent *> (event);
        switch(KEvent->key()){
        case Qt::Key_Up: Keys[0] = true; break;
        case Qt::Key_Down: Keys[1] = true; break;
        case Qt::Key_Left: Keys[2] = true; break;
        case Qt::Key_Right: Keys[3] = true; break;
        case Qt::Key_Space: Keys[4] = true; break;
        case Qt::Key_Return: Keys[5] = true; break;
        case Qt::Key_Backspace: Keys[33] = true; break;
        case Qt::Key_Shift: Keys[34] = true; break;
        default: //6->31
            if(KEvent->key()>=0x41 && KEvent->key()<=0x5a){
                Keys[KEvent->key()-(0x41-6)] = true;
            }break;
        }
    }
    else if(event->type() == QEvent::KeyRelease){
        QKeyEvent *KEvent = static_cast<QKeyEvent *> (event);
        switch(KEvent->key()){
        case Qt::Key_Up: Keys[0] = false; break;
        case Qt::Key_Down: Keys[1] = false; break;
        case Qt::Key_Left: Keys[2] = false; break;
        case Qt::Key_Right: Keys[3] = false; break;
        case Qt::Key_Space: Keys[4] = false; break;
        case Qt::Key_Return: Keys[5] = false; break;
        case Qt::Key_Backspace: Keys[33] = false; break;
        case Qt::Key_Shift: Keys[34] = false; break;
        default://6->31
            if(KEvent->key()>=0x41 && KEvent->key()<=0x5a){
                Keys[KEvent->key()-(0x41-6)] = false;
            }break;
        }
    }
    else if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent *MEvent = static_cast<QMouseEvent *> (event);

        Mouse = true;
        MouseXP = MEvent->x();
        MouseYP = MEvent->y();
    }
    else if(event->type() == QEvent::MouseButtonRelease){
        QMouseEvent *MEvent = static_cast<QMouseEvent *> (event);

        Mouse = false;
        MouseXR = MEvent->x();
        MouseYR = MEvent->y();
    }

    return QWidget::event(event);
}
