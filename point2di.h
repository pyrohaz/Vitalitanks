#ifndef POINT2DI
#define POINT2DI

#include <stdint.h>

class Point2DI{
public:
    Point2DI(){
        lX = 0; lY = 0;
    }

    Point2DI(int32_t X, int32_t Y){
        lX = X; lY = Y;
    }

    Point2DI(Point2DI &P){
        lX = P.lX; lY = P.lY;
    }

    ~Point2DI(){;}

    Point2DI& operator=(const Point2DI &P){
        if(this == &P){
            return *this;
        }

        lX = P.lX;
        lY = P.lY;

        return *this;
    }

    Point2DI& operator+=(const Point2DI &P){
        lX += P.lX;
        lY += P.lY;

        return *this;
    }

    Point2DI& operator-=(const Point2DI &P){
        lX -= P.lX;
        lY -= P.lY;

        return *this;
    }

    Point2DI& operator*=(const Point2DI &P){
        lX *= P.lX;
        lY *= P.lY;

        return *this;
    }

    bool operator==(const Point2DI &P) const{
        return (lX == P.lX) && (lY == P.lY);
    }

    bool operator!=(const Point2DI &P) const{
        return (lX != P.lX) || (lY != P.lY);
    }

    int32_t getX(void){ return lX; }
    int32_t getY(void){ return lY; }

    void setX(int32_t X){ lX = X; }
    void setY(int32_t Y){ lY = Y; }
    void setXY(int32_t X, int32_t Y){lX = X; lY = Y;}

    void Rotate(Point2DI P, float Deg){
        lX -= P.lX;
        lY -= P.lY;

        lX = (lX*cosf(Deg) - lY*sinf(Deg)) + P.lX;
        lY = (lY*sinf(Deg) + lY*cosf(Deg)) + P.lY;
    }

private:
    int32_t lX, lY;
};

#endif // POINT2DI

