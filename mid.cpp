#ifndef _MID_CPP
#define _MID_CPP
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include "allVariables.cpp"
#include "end.cpp"


static void calculate(){
    fight();
    for(int i = 0;i < 13;i ++){
        for(int j = 0;j < 11;j ++){
            switch(mapItem[i][j].type){
                case BASE: mapItem[i][j].force += 5;break;
                case SPECIAL: mapItem[i][j].force *= 1.4;break;
                case COMMON: mapItem[i][j].force *= 1.1;break;
            }
            if(!mapItem[i][j].force) mapItem[i][j].team = 0;
        }
    }
}
#endif _MID_CPP
