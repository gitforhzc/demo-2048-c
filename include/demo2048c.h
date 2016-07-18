/*************************************************************************
        > File Name: demo2048c.h
        > Author:
        > Mail:
        > Created Time: 2016年07月11日 星期一 02时12分45秒
 ************************************************************************/

#ifndef _DEMO2048C_H

/*
        global variable
*/
// 4*4方格
int a[4][4];
// 方格里空格的个数
int empty, movable;
int old_y, old_x;

/*
        global function
*/
void draw();
void play();
void init();
void init_number(int number);
void draw_one(int y, int x);
void left();
void right();
void up();
void down();
void cnt_value(int *new_y, int *new_x);
int game_over();
int cnt_one(int y, int x);

#define _DEMO2048C_H
#endif
