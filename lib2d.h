#ifndef LIB2D_H
#define LIB2D_H
#include "game.h"
class Game;

class lib2d
{
public:
    lib2d();
    lib2d(Game *G){
        lGame = G;
    }

    //Draw functions
    uint32_t PChar(uint16_t Ch, int32_t X, int32_t Y, uint8_t Size, QRgb TxtCol, QRgb BkgCol);
    uint32_t PChar(uint16_t Ch, Point2DI P, uint8_t Size, QRgb TxtCol, QRgb BkgCol){
        lib2d::PChar(Ch, P.getX(), P.getY(), Size, TxtCol, BkgCol);
    }

    uint32_t PStr(char *Str, int32_t X, int32_t Y, uint8_t Size, QRgb TxtCol, QRgb BkgCol);
    uint32_t PStr(char *Str, Point2DI P, uint8_t Size, QRgb TxtCol, QRgb BkgCol){
        lib2d::PStr(Str, P.getX(), P.getY(), Size, TxtCol, BkgCol);
    }

    uint32_t PNum(int32_t Num, int32_t X, int32_t Y, uint8_t Size, uint8_t Padding, QRgb TxtCol, QRgb BkgCol);
    uint32_t PNum(int32_t Num, Point2DI P, uint8_t Size, uint8_t Padding, QRgb TxtCol, QRgb BkgCol){
        lib2d::PNum(Num, P.getX(), P.getY(), Size, Padding, TxtCol, BkgCol);
    }
    uint32_t PNum(uint32_t Num, int32_t X, int32_t Y, uint8_t Size, uint8_t Padding, QRgb TxtCol, QRgb BkgCol){
        return lib2d::PNum((int32_t)Num, X, Y, Size, Padding, TxtCol, BkgCol);
    }
    uint32_t PNum(uint32_t Num, Point2DI P, uint8_t Size, uint8_t Padding, QRgb TxtCol, QRgb BkgCol){
        return lib2d::PNum((int32_t)Num, P.getX(), P.getY(), Size, Padding, TxtCol, BkgCol);
    }

    uint32_t PNumF(float Num, int32_t X, int32_t Y, uint8_t Size, uint8_t Precision, QRgb TxtCol, QRgb BkgCol);
    uint32_t PNumF(float Num, Point2DI P, uint8_t Size, uint8_t Precision, QRgb TxtCol, QRgb BkgCol){
        return lib2d::PNumF(Num, P.getX(), P.getY(), Size, Precision, TxtCol, BkgCol);
    }

    void sDrawLine(int32_t XS, int32_t YS, int32_t XE, int32_t YE, QRgb Col);
    void sDrawLine(Point2DI PS, Point2DI PE, QRgb Col){
        lib2d::sDrawLine(PS.getX(), PS.getY(), PE.getX(), PE.getY(), Col);
    }

    void DrawLine(int32_t XS, int32_t YS, int32_t XE, int32_t YE, int32_t Thickness, QRgb Col);
    void DrawLine(Point2DI PS, Point2DI PE, int32_t Thickness, QRgb Col){
        lib2d::DrawLine(PS.getX(), PS.getY(), PE.getX(), PE.getY(), Thickness, Col);
    }

    void DrawFillC(int32_t X, int32_t Y, int32_t R, QRgb Col);
    void DrawFillC(Point2DI P, int32_t R, QRgb Col){
        lib2d::DrawFillC(P.getX(), P.getY(), R, Col);
    }

    void DrawCircle(int32_t X, int32_t Y, int32_t R, QRgb Col);
    void DrawCircle(Point2DI P, int32_t R, QRgb Col){
        lib2d::DrawCircle(P.getX(), P.getY(), R, Col);
    }

    void DrawFillRec(int32_t XS, int32_t YS, int32_t XE, int32_t YE, QRgb Col);
    void DrawFillRec(Point2DI PS, Point2DI PE, QRgb Col){
        lib2d::DrawFillRec(PS.getX(), PS.getY(), PE.getX(), PE.getY(), Col);
    }

    void DrawRec(int32_t XS, int32_t YS, int32_t XE, int32_t YE, uint32_t Thickness, QRgb Col);
    void DrawRec(Point2DI PS, Point2DI PE, uint32_t Thickness, QRgb Col){
        lib2d::DrawRec(PS.getX(), PS.getY(), PE.getX(), PE.getY(), Thickness, Col);
    }

    //Co-ordinate cliEEing
    void ClipCo(int32_t *X, int32_t *Y);
    void ClipCo(float *X, float *Y);

private:
    Game *lGame;
};

#endif // LIB2D_H
