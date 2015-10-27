#ifndef NODE_H
#define NODE_H

#include "point2di.h"

class Node
{
public:
    Node(){
        lN = -1;
        lP.setXY(0,0);
    }

    Node(int32_t X, int32_t Y, int32_t Num){
        lP.setXY(X,Y);
        lN = Num;
    }

    Node(Point2DI P, int32_t Num){
        lP = P;
        lN = Num;
    }

    Node(const Node &N){
        lP = N.lP;
        lN = N.lN;
    }

    Node& operator=(const Node &N){
        if(&N == this){
            return *this;
        }
        lP = N.lP;
        lN = N.lN;

        return *this;
    }

    Point2DI& getPoint(void){
        return lP;
    }

    void setPoint(Point2DI P){
        lP = P;
    }

    int32_t getN(void){
        return lN;
    }

    void setN(int32_t N){
        lN = N;
    }

private:
    Point2DI lP;
    int32_t lN;
};

#endif // NODE_H
