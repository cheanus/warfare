#ifndef _START_CPP
#define _START_CPP
#include <stdio.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include "allVariables.cpp"


static void show(){
    char num[10];ITEM item;
    IMAGE background;
    loadimage(&background, "./res/background.png", WINWIDTH, WINHEIGHT);
    putimage(0, 0, &background);
    settextstyle(24, 8, "微软雅黑");
    for(int i = 0;i < 13;i ++){
        for(int j = 0;j < 11;j ++){
            item = mapItem[i][j];
            if(!item.team) continue;
            setfillcolor(teamColor[item.team - 1]);
            solidcircle(item.x + WINWIDTH / 30, item.y + WINHEIGHT / 27, WINHEIGHT / 80);
            sprintf(num, "%d", item.force);
            settextcolor(teamColor[item.team - 1]);
            outtextxy(item.x + WINWIDTH / 15 - textwidth(num), item.y + WINHEIGHT / 27 - textheight(num), num);
        }
    }
}

static void removeOut() {
    memset(alive, 0, 3 * sizeof(int));
    for(int i = 0; i < 11; i++)
        for(int j = 0; j < 13; j++)
                if(mapItem[j][i].team) alive[mapItem[j][i].team - 1] = 1;
} //删除已死亡的队伍

static void putHelp(){
    IMAGE help;
    ExMessage m;
    loadimage(&help, "./res/help.png", WINWIDTH, WINHEIGHT);
    putimage(0, 0, &help);
    while(1){
        m = getmessage(EM_MOUSE);
        if(m.message == WM_LBUTTONDOWN) break;
    }
}
#endif  _START_CPP
