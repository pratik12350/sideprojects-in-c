#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char *argv[]) {
  WINDOW *win = initscr();
  keypad(win, true);
  nodelay(win, true);

  int posX = 0, posY = 0;

  srand(time(NULL));
  int foodX = rand() % 30, foodY = rand() % 30;
  int dirX = 0, dirY = 1;

  while (true) {
    int keyPressed = wgetch(win);
    if (keyPressed == KEY_UP) {
      dirX = 0;
      dirY = -1;
    } else if (keyPressed == KEY_DOWN) {
      dirX = 0;
      dirY = 1;
    } else if (keyPressed == KEY_RIGHT) {
      dirX = 1;
      dirY = 0;
    } else if (keyPressed == KEY_LEFT) {
      dirX = -1;
      dirY = 0;
    }

    posX += dirX;
    posY += dirY;
    erase();
    mvaddstr(posY, posX, "*");
    mvaddstr(foodY, foodX, "&");

    if (foodX == posX && foodY == posY) {
      foodX = rand() % 30;
      foodY = rand() % 30;
    }
    usleep(100000);
  }
  endwin();
  printf("Game over!");
  return 0;
}
