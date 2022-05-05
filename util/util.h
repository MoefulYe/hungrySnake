/*
*util对一些常用的工具进行封装
*/
#include<stdio.h>
#ifndef UTIL_INCLUDED
#define UTIL_INCLUDED
#define CLEAR() printf("\033[2J")

// 定位光标

#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))

// 光标复位

#define RESET_CURSOR() printf("\033[H")

// 隐藏光标

#define HIDE_CURSOR() printf("\033[?25l")

// 显示光标

#define SHOW_CURSOR() printf("\033[?25h")

//反显

#define HIGHT_LIGHT() printf("\033[7m")

#define UN_HIGHT_LIGHT() printf("\033[27m")
char kbhit();
char getch()
#endif //UTIL_INCLUDED
