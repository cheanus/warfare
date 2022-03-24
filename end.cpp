#ifndef _END_CPP
#define _END_CPP
#include <algorithm>
#include <graphics.h>
#include <conio.h>
#include "allVariables.cpp"


static void fight() {
    for(int k = 0; k < 3; k ++) {
        for(int i = 0; i < 11; i++) {
            for(int j = 0; j < 13; j++) {
                for(int l = 0;l < 8;l ++){
                    if(mapItem[j][i].type == 0) continue;
                    int a = TACTICS[k][j][i][l].start.row, b = TACTICS[k][j][i][l].start.col;
                    TACTICS[k][j][i][l].force = std::min(mapItem[a][b].force, TACTICS[k][j][i][l].force);
                    if(!TACTICS[k][j][i][l].isExist || !TACTICS[k][j][i][l].force
                       || TACTICS[k][j][i][l].force <= 0 || mapItem[a][b].team != k + 1)
                        continue;
                    mapItem[a][b].force -= TACTICS[k][j][i][l].force;
                    if(mapItem[j][i].team == k + 1) mapItem[j][i].force += TACTICS[k][j][i][l].force;
                    else mapItem[j][i].force -= TACTICS[k][j][i][l].force;
                    if(mapItem[j][i].force < 0){
                        mapItem[j][i].team = mapItem[a][b].team;
                        mapItem[j][i].force *= -1;
                    }
                }
            }
        }
    }
}

static int winner() {
    int citySum[3];
    for(int i = 0; i < 11; i++)
        for(int j = 0; j < 13; j++)
            for(int k = 0;k < 3;k ++)
                if(mapItem[j][i].team == 2 - k) citySum[2 - k] ++; //逆序
    return std::max_element(citySum, citySum + 3) - citySum; //注意返回的是0,1,2.要改顺序
}

static int isOver(){
    return !(alive[0] * alive[1] * alive[2]);
}

static void over(){
    char s[100];
    sprintf(s, "The winner is player %d. Congratulations!\nPress any key to finish.", winner() + 1);
    MessageBox(hWnd, s, "win", MB_OK);
}
#endif _END_CPP
