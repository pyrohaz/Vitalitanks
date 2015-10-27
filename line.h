#ifndef LINE
#define LINE

#include "node.h"
#include "material.h"

class Node;
class Material;

class Line{
public:
    Material lMaterial;
    Line(){
        lNum = -1;
        lThickness = 1;
    }

    Line(Node Start, Node End, float Thickness){
        lStart = Start;
        lEnd = End;
        lThickness = Thickness;
    }

    Line& operator=(const Line &L){
        if(&L == this){
            return *this;
        }

        lStart = L.lStart;
        lEnd = L.lEnd;

        return *this;
    }

    Node getStart(void){
        return lStart;
    }

    Node getEnd(void){
        return lEnd;
    }

    int32_t getN(void){
        return lNum;
    }

    float getThickness(void){
        return lThickness;
    }

    void setStart(Node &Start){
        lStart = Start;
    }

    void setEnd(Node &End){
        lEnd = End;
    }

    void setN(int32_t N){
        lNum = N;
    }

    void setThickness(float Thickness){
        lThickness = Thickness;
    }

private:
    Node lStart, lEnd;
    int32_t lNum;
    float lThickness;
};

#endif // LINE

