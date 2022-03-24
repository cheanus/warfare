#ifndef _ALLVARIABLES_CPP
#define _ALLVARIABLES_CPP
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#define WINWIDTH 1000 //窗口宽度
#define WINHEIGHT 600 //窗口高度

static const int BASE = 1, //领地类型：大本营
    SPECIAL = 2, //特殊领地
    COMMON = 3, //普通领地
    BLANK = 4; //未占领地

typedef struct tagITEM{
    int type; //领地类型，0表示无效
    int team; //队伍，用整数1、2、3表示
    int force; //领地兵力数目
    double x;
    double y;
}ITEM; //单元格基本信息

typedef struct tagROWCOL{
    int row;
    int col;
}ROWCOL; //表示某个单元格的行标列标

static struct tagTACTICS{
    int isExist; //策略存在为1，否则为0
    ROWCOL start; //起点
    ROWCOL end; //终点
    int force; //所派兵力
}TACTICS[3][13][11][8]; //三人策略集合，13*11对应end单元格行标列标, 8对应不同的start

static ITEM mapItem[13][11]; //13*11简化地图单元格数组
static ROWCOL mark[27][15]; //窗口27*15分块单元格数组
static int alive[3] = {1, 1, 1}; //第i个1表示i玩家仍存活
static int teamColor[3] = {RED, BLUE, GREEN}; //代表第i个队伍颜色
static HWND hWnd;

static void initVariables(){
    for(int i = 2;i <= 7;i ++)
        for(int j = 3;j <= 7;j ++)
            mapItem[i][j].type = BLANK;

    mapItem[0][5].type = mapItem[8][0].type = mapItem[8][10].type = BASE;
    mapItem[1][0].type = mapItem[1][10].type = mapItem[5][5].type = mapItem[12][5].type = SPECIAL;
    mapItem[2][3].type = mapItem[2][5].type = mapItem[2][7].type
    = mapItem[4][2].type = mapItem[4][4].type = mapItem[4][6].type = mapItem[4][8].type
    = mapItem[6][2].type = mapItem[6][4].type = mapItem[6][6].type = mapItem[6][8].type = mapItem[8][4].type = mapItem[8][6].type = COMMON;
    mapItem[1][1].type = mapItem[1][2].type = mapItem[1][5].type = mapItem[1][8].type = mapItem[1][9].type
    = mapItem[2][0].type = mapItem[2][2].type = mapItem[2][8].type = mapItem[2][10].type
    = mapItem[3][0].type = mapItem[3][1].type = mapItem[3][9].type = mapItem[2][10].type
    = mapItem[5][1].type = mapItem[5][2].type = mapItem[5][8].type= mapItem[5][9].type
    = mapItem[7][1].type = mapItem[7][9].type = mapItem[8][5].type
    = mapItem[9][4].type = mapItem[9][6].type = mapItem[10][4].type = mapItem[10][6].type
    = mapItem[11][4].type = mapItem[11][6].type
    = BLANK;

    mapItem[0][5].team = 1;mapItem[8][0].team = 2;mapItem[8][10].team = 3;
    mapItem[0][5].force = 25;mapItem[8][0].force = 25;mapItem[8][10].force = 25;

    for(int i = 0;i < 13;i ++){
        for(int j = 0;j < 11;j ++){
            mapItem[i][j].x = WINWIDTH / 15.0 * (j + 2);
            mapItem[i][j].y = WINHEIGHT / 27.0 * (2 * i + 1);
            if(mapItem[i][j].type){
                mark[2 * i + 1][j + 2].row = i;mark[2 * i + 2][j + 2].row = i;
                mark[2 * i + 1][j + 2].col = j;mark[2 * i + 2][j + 2].col = j;
            }
        }
    }

    for(int i = 0;i < 27;i ++){
        for(int j = 0;j < 15;j ++){
            if((abs(i - 1) | abs(j - 7)) <= 1) mark[i][j].row = 0, mark[i][j].col = 5;
            if((abs(i - 18) | abs(j - 1)) <= 1) mark[i][j].row = 8, mark[i][j].col = 0;
            if((abs(i - 18) | abs(j - 13)) <= 1) mark[i][j].row = 8, mark[i][j].col = 10;
        }
    }

    mapItem[0][5].y = WINHEIGHT / 27.0 * 0.5;
    mapItem[8][0].x = WINWIDTH / 15.0 * 1;mapItem[8][0].y = WINHEIGHT / 27.0 * 17.5;
    mapItem[8][10].x = WINWIDTH / 15.0 * 13;mapItem[8][10].y = WINHEIGHT / 27.0 * 17.5;

    setbkmode(TRANSPARENT);
    hWnd = GetHWnd();
    SetWindowText(hWnd,"warfare");
}// 初始化全局变量

static void refreshVariables(){
    memset(TACTICS, 0, 3 * 13 * 11 * 8 * sizeof(struct tagTACTICS));
} //刷新全局变量

static ROWCOL getMouseRC(ExMessage m){
    int a = 27.0 * m.y / WINHEIGHT, b = 15.0 * m.x / WINWIDTH;
    return mark[a][b];
}//返回鼠标点击的单元格的行标列标

#endif  _ALLVARIABLES_CPP
