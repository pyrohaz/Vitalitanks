#include "game.h"
#include "node.h"
#include "line.h"

extern bool Mouse, Keys[];
extern uint32_t MouseXP, MouseYP;
extern uint32_t MouseXR, MouseYR;

#define MAX_NODES   100
#define MAX_LINES   100

#define TXT_SIZE    2
#define TXT_COL     qRgb(255,255,255)
#define TBKG_COL    qRgb(0,0,0)

void Game::DrawGame(void){
    Material BlackAshWood("Black Ash Wood", 0.54e3, 1.0825e+7, qRgb(165,50,50));
    Material Aluminium6061("6061 Aluminium", 2.7e3, 0.27e9, qRgb(150,150,150));
    Material Steel1045("AISI 1045 Steel", 7.7e3, 0.585e9, qRgb(100,100,100));
    Material Polypropylene("Polypropylene", 0.9e3, 0.033e9, qRgb(200,0,0));
    Material CarbonEpoxy("Carbon epoxy", 1.6e3, 142e9, qRgb(20,20,20));

    static lib2d L2(this);
    static Node Nodes[MAX_NODES];
    static Line Lines[MAX_LINES];

    //Node counter and line counter
    static uint8_t NCnt = 0, LCnt = 0;

    static uint8_t CMaterial = 0;

    static bool DrawMode = false;
    static bool MouseOld = false;

    static uint8_t LinePoint = 0;

    Point2DI TP;
    uint8_t Cnt;
    uint32_t XPos;

    //Clear the screen to black
    pQI->fill(Qt::black);

    XPos = L2.PStr("Nodes: ", 0, 64, 1, TXT_COL, TBKG_COL);
    L2.PNum(NCnt, XPos, 64, 1, 0, TXT_COL, TBKG_COL);

    XPos = L2.PStr("Lines: ", 0, 80, 1, TXT_COL, TBKG_COL);
    L2.PNum(LCnt, XPos, 80, 1, 0, TXT_COL, TBKG_COL);

    if(!DrawMode){
        L2.PStr("Draw Node", 0, 0, TXT_SIZE, TXT_COL, TBKG_COL);
    }
    else{
        L2.PStr("Draw Line", 0, 0, TXT_SIZE, TXT_COL, TBKG_COL);

        if(LinePoint == 0){
            L2.PStr("Line start point", 0, 32, 1, TXT_COL, TBKG_COL);
        }
        else{
            L2.PStr("Line end point", 0, 32, 1, TXT_COL, TBKG_COL);
        }

        XPos = L2.PStr("Material: ", 0, 48, 1, TXT_COL, TBKG_COL);

        switch(CMaterial){
        case 0: L2.PStr((char *)BlackAshWood.getName().c_str(), XPos, 48, 1, TXT_COL, TBKG_COL); break;
        case 1: L2.PStr((char *)Aluminium6061.getName().c_str(), XPos, 48, 1, TXT_COL, TBKG_COL); break;
        case 2: L2.PStr((char *)Steel1045.getName().c_str(), XPos, 48, 1, TXT_COL, TBKG_COL); break;
        case 3: L2.PStr((char *)Polypropylene.getName().c_str(), XPos, 48, 1, TXT_COL, TBKG_COL); break;
        case 4: L2.PStr((char *)CarbonEpoxy.getName().c_str(), XPos, 48, 1, TXT_COL, TBKG_COL); break;
        }
/*
        const char *Str;
        switch(CMaterial){
        case 0: Str = BlackAshWood.getName().c_str(); break;
        case 1: Str = Aluminium6061.getName().c_str(); break;
        case 2: Str = Steel1045.getName().c_str(); break;
        case 3: Str = Polypropylene.getName().c_str(); break;
        case 4: Str = CarbonEpoxy.getName().c_str(); break;
        }

        L2.PStr((char *)Str, XPos, 48, 1, TXT_COL, TBKG_COL);*/
    }

    //Upon mouse click/release
    if(MouseOld != Mouse){
        MouseOld = Mouse;
        //Populate point with mouse click co-ordinates
        TP.setXY(MouseXP, MouseYP);

        if(Mouse){
            //Check to see if draw mode has changed
            if(MouseXP < ((6*(TXT_SIZE+1))*9) && MouseYP < (8*(TXT_SIZE+1))){
                DrawMode = !DrawMode;

                //Start with first point
                if(DrawMode){
                    LinePoint = 0;
                }
            }
            else if(DrawMode && MouseXP < XPos && MouseYP < 64 && MouseYP >= 48){ //Change material
                CMaterial++;
                CMaterial%=5;
            }
            else if(!DrawMode){ //Draw node
                //If mouse is clicked (true) and total node count isn't reached
                if(Mouse && NCnt<MAX_NODES){
                    //Check to see if current click matches any previous nodes
                    //Set node
                    for(Cnt = 0; Cnt<MAX_NODES; Cnt++){
                        if(Nodes[Cnt].getPoint() == TP){
                            break;
                        }
                    }
                    if(Cnt == MAX_NODES){
                        Nodes[NCnt].setPoint(TP);
                        Nodes[NCnt].setN(NCnt);
                        NCnt++;
                    }
                }
            }
            else if(DrawMode){ //Draw Line
                if(LCnt<MAX_LINES){
                    int32_t ClosestNodeN, NodeCnt;
                    int32_t Distance = INT_MAX;

                    //Search for closest node to click
                    for(Cnt = 0; Cnt<MAX_NODES; Cnt++){
                        if(Nodes[Cnt].getN() != -1){
                            if(TP.Distance(Nodes[Cnt].getPoint()) < Distance){
                                Distance = TP.Distance(Nodes[Cnt].getPoint());
                                ClosestNodeN = Nodes[Cnt].getN();
                                NodeCnt = Cnt;
                            }
                        }
                    }

                    if(LinePoint == 0){
                        Lines[LCnt].setStart(Nodes[NodeCnt]);
                        LinePoint = 1;
                    }
                    else{
                        //Ensure lines aren't drawn to the same node!
                        if(Nodes[NodeCnt].getN() != Lines[LCnt].getStart().getN()){
                            LinePoint = 0;
                            Lines[LCnt].setEnd(Nodes[NodeCnt]);
                            Lines[LCnt].setN(LCnt);

                            switch(CMaterial){
                            case 0:
                                Lines[LCnt].lMaterial = BlackAshWood;
                                break;
                            case 1:
                                Lines[LCnt].lMaterial = Aluminium6061;
                                break;
                            case 2:
                                Lines[LCnt].lMaterial = Steel1045;
                                break;
                            case 3:
                                Lines[LCnt].lMaterial = Polypropylene;
                                break;
                            case 4:
                                Lines[LCnt].lMaterial = CarbonEpoxy;
                                break;
                            }

                            LCnt++;
                        }
                    }
                }
            }
        }
    }

    //Draw nodes
    for(Cnt = 0; Cnt<MAX_NODES; Cnt++){
        //Ensure node exists! Default initializer for node num is -1, anything > -1 will exist
        if(Nodes[Cnt].getN() != -1){
            L2.DrawFillC(Nodes[Cnt].getPoint(), 3, qRgb(0, 255, 0));
            L2.PNum(Nodes[Cnt].getN(), Nodes[Cnt].getPoint(), 0, 0, TXT_COL, TBKG_COL);
        }
    }

    //Draw lines
    for(Cnt = 0; Cnt<MAX_LINES; Cnt++){
        if(Lines[Cnt].getN() != -1){
            L2.DrawLine(Lines[Cnt].getStart().getPoint(), Lines[Cnt].getEnd().getPoint(), 0, Lines[Cnt].lMaterial.getColour());

            L2.PNum(Lines[Cnt].getN(), Lines[Cnt].getStart().getPoint().Midpoint(Lines[Cnt].getEnd().getPoint()), 0, 0, TXT_COL, TBKG_COL);
        }
    }
}
