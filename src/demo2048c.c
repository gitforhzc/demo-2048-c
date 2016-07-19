/*************************************************************************
        > File Name: demo2048c.c
        > Author:
        > Mail:
        > Created Time: 2016年07月11日 星期一 02时15分57秒
 ************************************************************************/
#include "demo2048c.h"
#include "stdafx.h"
// init 函数首先初始化屏幕，在方格中随机生成一个位置并放入数字2，4。
void init() {
  initscr();
  cbreak();
  noecho();
  curs_set(0);

  empty = sizeof(a) / sizeof(a[0][0]);
  srand(time(0));
  add_number();
  add_number();
  draw();
}

// 用 wsad 来表示上下左右方向
void play() {

  int old_empty;
  char ch;

  while (1) {
    moved = 0;
    old_empty = empty;

    ch = getch();
    switch (ch) {
    case 'A':
    case 'a':
      left();
      break;
    case 'D':
    case 'd':
      right();
      break;
    case 'W':
    case 'w':
      up();
      break;
    case 'S':
    case 's':
      down();
      break;
    case 'Q':
    case 'q':
      endflag = -1;
      break;
    default:
      continue;
      break;
    }

    draw(); // refresh
    if (empty <= 0 && test_lose()) {
      endflag = 1;
    }

    if (endflag == -1 || endflag == 1 || endflag == 2) {
      game_over();
    }

    //生成新方块
    if ((empty != old_empty) ||
        (moved == 1)) { //修复了不移动或不消除方块也生成新方块的bug
      add_number();
      draw();
    }
  }
}

// 游戏结束子函数
int game_over() {

  draw_over();
  sleep(1);
  endwin();
  exit(0);
}

int test_lose() {
  int y, x, j, i;
  for (y = 0; y < 4; y++)
    for (x = 0; x < 3; x++)
      if (a[y][x] == a[y + 1][x] || a[y][x] == a[y][x + 1]) {
        return 0;
      }
  x = 3;
  for (y = 0; y < 3; y++)
    if (a[y][3] == a[y + 1][3]) {
      return 0;
    }
  y = 3;
  for (x = 0; x < 3; x++)
    if (a[3][x] == a[3][x + 1]) {
      return 0;
    }

  return 1;
}

// add_number 函数用于生成随机数
void add_number() {
  int new_x, new_y, tmp;
  do {
    new_x = rand() % 4;
    new_y = rand() % 4;
  } while (a[new_y][new_x] != 0);

  do {
    tmp = rand() % 4;
  } while (tmp == 0 || tmp == 2);
  a[new_y][new_x] = tmp + 1;
  empty--;
}

// draw绘制方格
void draw() {
  int n, m, x, y;
  char c[4] = {'0', '0', '0', '0'};

  clear();
  for (n = 0; n < 9; n += 2) //横线
    for (m = 0; m < 21; m++) {
      move(n, m);
      addch('-');
      refresh();
    }
  for (m = 0; m < 22; m += 5) //竖线
    for (n = 1; n < 8; n++) {
      move(n, m);
      addch('|');
      refresh();
    }
  for (y = 0; y < 4; y++) //数字
    for (x = 0; x < 4; x++) {
      draw_one(y, x);
      if (a[y][x] == 64) {
        endflag = 2;
      }
    }
}

// draw_one 函数用于绘制单个数字
void draw_one(int y, int x) {
  int i, m, k, j;
  char c[4] = {'0', '0', '0', '0'};

  i = a[y][x];
  m = 0;
  do {
    j = i % 10;
    c[m++] = j + '0';
    i = i / 10;
  } while (i > 0);
  m = 0;
  k = (x + 1) * 5 - 1;
  while (c[m] != '0') {
    move(2 * y + 1, k);
    addch(c[m++]);
    k--;
  }
}

void left() {
  int x, y, i;
  //从左向右消去相同方块
  for (y = 0; y < 4; y++)
    for (x = 0; x < 4;) {
      if (a[y][x] == 0) {
        x++;
        continue;
      } else {
        for (i = x + 1; i < 4; i++) {
          if (a[y][i] == 0) {
            continue;
          } else {
            if (a[y][x] == a[y][i]) {
              a[y][x] += a[y][i];
              a[y][i] = 0;
              x = i + 1;
              empty++;
              break;
            } else {
              x = i;
              break;
            }
          }
        }
        x = i;
      }
    }
  //向左移动方块
  for (y = 0; y < 4; y++)
    for (x = 0; x < 4; x++) {
      if (a[y][x] == 0) {
        continue;
      } else {
        for (i = x; (i > 0) && (a[y][i - 1] == 0); i--) {
          a[y][i - 1] = a[y][i];
          a[y][i] = 0;
          moved = 1;
        }
      }
    }
}

void right() {
  int x, y, i;
  //从右向左消去相同方块
  for (y = 0; y < 4; y++)
    for (x = 3; x >= 0;) {
      if (a[y][x] == 0) {
        x--;
        continue;
      } else {
        for (i = x - 1; i >= 0; i--) {
          if (a[y][i] == 0) {
            continue;
          } else if (a[y][x] == a[y][i]) {
            a[y][x] += a[y][i];
            a[y][i] = 0;
            x = i - 1;
            empty++;
            break;
          } else {
            x = i;
            break;
          }
        }
        x = i;
      }
    }
  //向右移动方块
  for (y = 0; y < 4; y++)
    for (x = 3; x >= 0; x--) {
      if (a[y][x] == 0) {
        continue;
      } else {
        for (i = x; (i < 3) && (a[y][i + 1] == 0); i++) {
          a[y][i + 1] = a[y][i];
          a[y][i] = 0;
          moved = 1;
        }
      }
    }
}

void up() {
  int x, y, i;
  //从上向下消去相同方块
  for (x = 0; x < 4; x++)
    for (y = 0; y < 4;) {
      if (a[y][x] == 0) {
        y++;
        continue;
      } else {
        for (i = y + 1; i < 4; i++) {
          if (a[i][x] == 0) {
            continue;
          } else if (a[y][x] == a[i][x]) {
            a[y][x] += a[i][x];
            a[i][x] = 0;
            y = i + 1;
            empty++;
            break;
          } else {
            y = i;
            break;
          }
        }
        y = i;
      }
    }
  //向上移动方块
  for (x = 0; x < 4; x++)
    for (y = 0; y < 4; y++) {
      if (a[y][x] == 0) {
        continue;
      } else {
        for (i = y; (i > 0) && (a[i - 1][x] == 0); i--) {
          a[i - 1][x] = a[i][x];
          a[i][x] = 0;
          moved = 1;
        }
      }
    }
}

void down() {
  int x, y, i;
  //从下向上消去相同方块
  for (x = 0; x < 4; x++)
    for (y = 3; y >= 0;) {
      if (a[y][x] == 0) {
        y--;
        continue;
      } else {
        for (i = y - 1; i >= 0; i--) {
          if (a[i][x] == 0) {
            continue;
          } else if (a[y][x] == a[i][x]) {
            a[y][x] += a[i][x];
            a[i][x] = 0;
            y = i - 1;
            empty++;
            break;
          } else {
            y = i;
            break;
          }
        }
        y = i;
      }
    }
  //向下移动方块
  for (x = 0; x < 4; x++)
    for (y = 3; y >= 0; y--) {
      if (a[y][x] == 0) {
        continue;
      } else {
        for (i = y; (i < 3) && (a[i + 1][x] == 0); i++) {
          a[i + 1][x] = a[i][x];
          a[i][x] = 0;
          moved = 1;
        }
      }
    }
}

void draw_over() {
  int y = 9, x = 0;
  char output[30];

  switch (endflag) {
  case 1:
    strcpy(output, "You lose! ");
    break;
  case 2:
    strcpy(output, "You win! ");
    break;
  case -1:
    strcpy(output, "");
    break;
  }
  strcat(output, "Enter any key to quit.");

  for (int i = 0; output[i] != '\0'; i++, x++) {
    move(y, x);
    addch(output[i]);
  }
  refresh();
  char chtmp = getch();
}
