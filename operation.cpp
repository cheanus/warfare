#ifndef _OPERATION_CPP
#define _OPERATION_CPP
#include <iostream>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include "allVariables.cpp"
#include "start.cpp"

static void showTactics(int n){
    ITEM item1, item2;
    char num[10];
    show();
    for(int i = 0;i < 13;i ++){
        for(int j = 0;j < 11;j ++){
            for(int k = 0;k < 8;k ++){
                if(TACTICS[n][i][j][k].isExist){
                    setcolor(teamColor[n]);
                    item1 = mapItem[TACTICS[n][i][j][k].start.row][TACTICS[n][i][j][k].start.col];
                    item2 = mapItem[TACTICS[n][i][j][k].end.row][TACTICS[n][i][j][k].end.col];
                    line(item1.x+WINWIDTH/30-10, item1.y+WINHEIGHT/27-10, item2.x+WINWIDTH/30, item2.y+WINHEIGHT/27);
                    line(item1.x+WINWIDTH/30-10, item1.y+WINHEIGHT/27+10, item2.x+WINWIDTH/30, item2.y+WINHEIGHT/27);
                    line(item1.x+WINWIDTH/30+10, item1.y+WINHEIGHT/27-10, item2.x+WINWIDTH/30, item2.y+WINHEIGHT/27);
                    line(item1.x+WINWIDTH/30+10, item1.y+WINHEIGHT/27+10, item2.x+WINWIDTH/30, item2.y+WINHEIGHT/27);
                    sprintf(num, "%d", TACTICS[n][i][j][k].force);
                    settextcolor(BLACK);
                    outtextxy((item1.x+item2.x-textwidth(num))/2 + WINWIDTH / 30, (item1.y+item2.y-textheight(num))/2 + WINHEIGHT / 27, num);
                }
            }
        }
    }
}

static int isStepLegal(int n, tagTACTICS cacheTactics){
    int x1 = cacheTactics.start.row, y1 = cacheTactics.start.col, x2 = cacheTactics.end.row, y2 = cacheTactics.end.col, startAttack[13][11];
    memset(startAttack, 0, 13 * 11 * sizeof(int));
    for(int i = 0;i < 13;i ++){
        for(int j = 0;j < 11;j ++){
            for(int k = 0;k < 8;k ++){
                if(cacheTactics.end.row == i && cacheTactics.end.col == j
                   && TACTICS[n][i][j][k].start.row == x1 && TACTICS[n][i][j][k].start.col == y1)
                    continue;
                startAttack[TACTICS[n][i][j][k].start.row][TACTICS[n][i][j][k].start.col] += TACTICS[n][i][j][k].force;
            }
        }
    }
    if(cacheTactics.isExist && mapItem[x1][y1].team == n + 1 && cacheTactics.force > 0
       && cacheTactics.force <= mapItem[x1][y1].force - startAttack[x1][y1]){
        if(   (y1 + y2 == 3 || y1 + y2 == 17) && x1 + x2 == 5
           || (y1 + y2 == 9 || y1 + y2 == 11) && (x1 + x2 == 9 || x1 + x2 == 11)){
            printf("illegal!\n");
            return 0;
        }
        if((abs(x1 - x2) | abs(y1 - y2)) == 1) return 1;
    }
    printf("illegal!\n");
    return 0;
}

static void operate(int n){
    ROWCOL rc;
    ExMessage m;
    struct tagTACTICS cacheTactics;
    memset(&cacheTactics, 0, sizeof(struct tagTACTICS));
    printf("player %d's turn starts\n", n + 1);
    while(1){
        m = getmessage(EM_MOUSE);
        switch(m.message){
            case WM_LBUTTONDBLCLK:
                system("cls");
                printf("player %d's turn ends\n", n + 1);
                return;
                break;
            case WM_LBUTTONDOWN:
                rc = getMouseRC(m);
                if(!mapItem[rc.row][rc.col].type) break;
                if(!cacheTactics.isExist){
                    cacheTactics.isExist = 1;
                    cacheTactics.start = rc;
                }else{
                    cacheTactics.end = rc;
                    printf("please input force:");
                    scanf("%d", &cacheTactics.force);
                    if(isStepLegal(n, cacheTactics)){
                        int k = 0, x = cacheTactics.end.row, y = cacheTactics.end.col;
                        while(k < 8 && TACTICS[n][x][y][k].isExist &&
                              (TACTICS[n][x][y][k].start.row != cacheTactics.start.row ||
                               TACTICS[n][x][y][k].start.col != cacheTactics.start.col)) k++;
                        TACTICS[n][x][y][k] = cacheTactics;
                    }
                    memset(&cacheTactics, 0, sizeof(struct tagTACTICS));
                    showTactics(n);
                }
                break;
            case WM_RBUTTONDOWN:
                memset(&cacheTactics, 0, sizeof(struct tagTACTICS));
                memset(&TACTICS[n], 0, 13 * 11 * 8 * sizeof(struct tagTACTICS));
                show();
                printf("your tactics are cleared\n");
                break;
        }
    }
}
#endif  _OPERATION_CPP
