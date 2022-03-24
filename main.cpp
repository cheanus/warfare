#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include "allVariables.cpp"
#include "operation.cpp"
#include "end.cpp"
#include "start.cpp"
#include "mid.cpp"

int main(){
    initgraph(WINWIDTH, WINHEIGHT, SHOWCONSOLE | EW_DBLCLKS);
    IMAGE background;
    loadimage(&background, "./res/background.png", WINWIDTH, WINHEIGHT);
    initVariables();
    putHelp();
    putimage(0, 0, &background);
    for(int k = 0;!isOver() && k < 32;k ++){
        removeOut();
        for(int i = 0;i < 3;i ++){
            printf("Round %d:\n", k + 1);
            if(!alive[i]){
                printf("Player %d is dead. Skip.\n", i + 1);
                continue;
            }
            show();
            operate(i);
            show();
            Sleep(400);
        }
        calculate();
        refreshVariables();
    }
    over();
    getch();
    closegraph();
    return 0;
}
