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
int empty, moved, endflag;
int old_y, old_x;

/*
        global function
*/
void init();
void add_number();
void draw();
void draw_one(int y, int x);
void play();
void left();
void right();
void up();
void down();
int game_over();
int test_lose();
void draw_over();

#define _DEMO2048C_H
#endif
