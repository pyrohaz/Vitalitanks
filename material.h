#ifndef MATERIAL
#define MATERIAL

#include <string>
#include <QRgb>

using namespace std;

class Material{
public:
    Material(){
        lName = "";
        lDensity = 0.0f;
        lUTS = 0.0f;
    }

    Material(string Name, float Density, float UTS, QRgb Col){
        lDensity = Density;
        lUTS = UTS;
        lName = Name;
        lCol = Col;
    }

    Material& operator=(const Material &M){
        if(&M == this){
            return *this;
        }

        lDensity = M.lDensity;
        lUTS = M.lUTS;
        lName = M.lName;
        lCol = M.lCol;

        return *this;
    }

    void setName(string Name){
        lName = Name;
    }

    string getName(void){
        return lName;
    }

    void setDensity(float Density){
        lDensity = Density;
    }

    void setUTS(float UTS){
        lUTS = UTS;
    }

    void setColour(QRgb Col){
        lCol = Col;
    }

    float getDensity(void){
        return lDensity;
    }

    float getUTS(void){
        return lUTS;
    }

    QRgb getColour(void){
        return lCol;
    }

private:
    float lDensity, lUTS;
    string lName;
    QRgb lCol;
};

#endif // MATERIAL

