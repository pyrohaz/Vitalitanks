#include "lib2d.h"
#include "Fonts.h"

const uint8_t *Chars = HFont1;

lib2d::lib2d()
{

}


uint32_t lib2d::PChar(uint16_t Ch, int32_t X, int32_t Y, uint8_t Size, QRgb TxtCol, QRgb BkgCol){
    uint32_t XCnt, YCnt, CharAddr, YPos;

    if(Ch<0x20) return X;
    Ch-=0x20;
    Ch*=5;

    if(Y >= (lGame->YRes-(8*(Size+1)))){
        Y = (lGame->YRes-(8*(Size+1)))-1;
    }

    if(X >= (lGame->XRes-(5*(Size+1)))){
        X = (lGame->XRes-(5*(Size+1)))-1;
    }

    for(YCnt = 0; YCnt<8*(Size+1); YCnt++){
        for(XCnt = 0; XCnt<(5*(1+Size)) + LetterSpace; XCnt++){
            CharAddr = XCnt/(Size+1);
            YPos = YCnt/(Size+1);
            if(XCnt<(5*(Size+1)) && (Chars[Ch+CharAddr] & (1UL<<YPos)))  lGame->DrawPix(X+XCnt, Y+YCnt, TxtCol);
            else if(BkgCol != qRgb(255,255,255)) lGame->DrawPix(X+XCnt, Y+YCnt, BkgCol);
        }
    }

    return X+(1+Size)*5+LetterSpace;
}

uint32_t lib2d::PStr(char *Str, int32_t X, int32_t Y, uint8_t Size, QRgb TxtCol, QRgb BkgCol){
    uint32_t StrLen = strlen(Str), Cnt;

    for(Cnt = 0; Cnt<StrLen; Cnt++){
        X = lib2d::PChar(Str[Cnt], X, Y, Size, TxtCol, BkgCol);
    }
    return X;
}

uint32_t lib2d::PNum(int32_t Num, int32_t X, int32_t Y, uint8_t Size, uint8_t Padding, QRgb TxtCol, QRgb BkgCol){
    char NBuf[15] = {0};
    char NSpec[4] = "%i";
    //NSpec[1] = Padding;

    sprintf(NBuf, NSpec, Num);
    return PStr(NBuf, X, Y, Size, TxtCol, BkgCol);
}

uint32_t lib2d::PNumF(float Num, int32_t X, int32_t Y, uint8_t Size, uint8_t Precision, QRgb TxtCol, QRgb BkgCol){
    char NBuf[40] = {0};
    char NSpec[4] = "%f";
    //NSpec[1] = Precision;

    sprintf(NBuf, NSpec, Num);
    return PStr(NBuf, X, Y, Size, TxtCol, BkgCol);
}

void lib2d::sDrawLine(int32_t XS, int32_t YS, int32_t XE, int32_t YE, QRgb Col){
    int dx = abs(XE-XS), sx = XS<XE ? 1 : -1;
    int dy = abs(YE-YS), sy = YS<YE ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;

    for(;;){
        lGame->DrawPix(XS, YS, Col);

        if (XS==XE && YS==YE) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; XS += sx; }
        if (e2 < dy) { err += dx; YS += sy; }
    }
}

void lib2d::DrawFillC(int32_t X, int32_t Y, int32_t R, QRgb Col){
    int x = R;
    int y = 0;
    int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

    while(x >= y)
    {

        sDrawLine(x + X,  y + Y, -x + X,  y + Y, Col);
        sDrawLine( y + X,  x + Y, -y + X,  x + Y, Col);
        sDrawLine(-x + X, -y + Y,  x + X, -y + Y, Col);
        sDrawLine(-y + X, -x + Y, y + X, -x + Y, Col);

        y++;
        if (decisionOver2<=0)
        {
            decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
        }
        else
        {
            x--;
            decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
        }
    }
}

void lib2d::DrawCircle(int32_t X, int32_t Y, int32_t R, QRgb Col){
    int x = R;
    int y = 0;
    int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

    while(x >= y)
    {

        lGame->DrawPix(x+X, y+Y, Col);
        lGame->DrawPix(-x+X, y+Y, Col);
        lGame->DrawPix(y+X, x+Y, Col);
        lGame->DrawPix(-y+X, x+Y, Col);
        lGame->DrawPix(-x+X, -y+Y, Col);
        lGame->DrawPix(x+X, -y+Y, Col);
        lGame->DrawPix(-y+X, -x+Y, Col);
        lGame->DrawPix(y+X, -x+Y, Col);

        y++;
        if (decisionOver2<=0)
        {
            decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
        }
        else
        {
            x--;
            decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
        }
    }
}

void lib2d::DrawLine(int32_t XS, int32_t YS, int32_t XE, int32_t YE, int32_t Thickness, QRgb Col){
    if(Thickness>1){
        int dx = abs(XE-XS), sx = XS<XE ? 1 : -1;
        int dy = abs(YE-YS), sy = YS<YE ? 1 : -1;
        int err = (dx>dy ? dx : -dy)/2, e2;

        for(;;){
            DrawFillC(XS, YS, Thickness/2, Col);

            if (XS==XE && YS==YE) break;
            e2 = err;
            if (e2 >-dx) { err -= dy; XS += sx; }
            if (e2 < dy) { err += dx; YS += sy; }
        }
    }
    else{
        sDrawLine(XS, YS, XE, YE, Col);
    }
}

void lib2d::DrawFillRec(int32_t XS, int32_t YS, int32_t XE, int32_t YE, QRgb Col){
    uint32_t X, Y;
    for(Y = YS; Y<YE; Y++){
        for(X = XS; X<XE; X++){
            lGame->DrawPix(X, Y, Col);
        }
    }
}

void lib2d::DrawRec(int32_t XS, int32_t YS, int32_t XE, int32_t YE, uint32_t Thickness, QRgb Col){
    DrawLine(XS, YS, XE, YS, Thickness, Col);
    DrawLine(XS, YE, XE, YE, Thickness, Col);
    DrawLine(XS, YS, XS, YE, Thickness, Col);
    DrawLine(XE, YS, XE, YE, Thickness, Col);
}

void lib2d::ClipCo(int32_t *X, int32_t *Y){
    if(*X>=lGame->XRes) *X = lGame->XRes-1;
    if(*X<0) *X = 0;

    if(*Y>=lGame->YRes) *Y = lGame->YRes-1;
    if(*Y<0) *Y = 0;
}

void lib2d::ClipCo(float *X, float *Y){
    if(*X>=lGame->XRes) *X = lGame->XRes-1;
    if(*X<0) *X = 0;

    if(*Y>=lGame->YRes) *Y = lGame->YRes-1;
    if(*Y<0) *Y = 0;
}
