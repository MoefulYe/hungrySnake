#include "./menu.h"
#include "../util/util.h"
#include<stdio.h>


int menu(){
    MOVETO(45,12);
    printf("Hungry Snake!");
    MOVETO(48,14);
    printf("1. start game!");
    MOVETO(48,16);
    printf("2. help");
    MOVETO(48,18);
    printf("3. about");
    MOVETO(48,20);
    printf("4. rank list");
    MOVETO(48,22);
    printf("press any other key to exit");
    HIDE_CURSOR();
    int res=getch()-'0';
    CLEAR();
    return res;
}

void help(){
    MOVETO(48,12);
    printf("use 'a' to turn left");
    MOVETO(48,14);
    printf("use 'd' to turn right");
    MOVETO(48,16);
    printf("gameover when the snake hit the wall or its body");
    MOVETO(48,18);
    printf("press any key to return the menu");
    while(!kbhit());
    CLEAR();

}

void about(){
    MOVETO(45,12);
    printf("produced by hanxinqiuyun");
    MOVETO(48,14);
    printf("powered by moefulye");
    MOVETO(48,16);
    printf("github:https://github.com/MoefulYe/hungrySnake");
    MOVETO(48,18);
    printf("press any key to return the menu");
    HIDE_CURSOR();
    while(!kbhit());
    CLEAR();
}