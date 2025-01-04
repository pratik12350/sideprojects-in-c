#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  int step;
  int prog;
  int id;
} Bar;

int BAR_LEN = 20;
int MAX_BARS = 13;
char PROGRESS_CHAR = '=';

void clearScreen();

// DROPPING BARS S🗣️🗣️
void dropBars(Bar bar);

int main() {
  srand(time(NULL));

  Bar bars[MAX_BARS];

  for (int i = 0; i < MAX_BARS; i++) {
    bars[i].step = rand() % 10 + 1;
    bars[i].id = i;
    bars[i].prog = 0;
  }

  int barFilled = 1;
  while (barFilled) {
    clearScreen();
    barFilled = 0;

    for (int i = 0; i < MAX_BARS; i++) {
      bars[i].prog += bars[i].step;

      if (bars[i].prog < 100) {
        barFilled = 1;
      } else if (bars[i].prog > 100) {
        bars[i].prog = 100;
      }

      dropBars(bars[i]);
    }
    sleep(1);
  }
  printf("Straight up bars 🗣️🗣️\n");
  return 0;
}

void dropBars(Bar bar) {
  int charsInBar = (bar.prog * BAR_LEN) / 100;
  int color = 31 + (bar.id % 6);

  printf("\033[1;%dmTask ID #%d [", color, bar.id);
  for (int i = 0; i < BAR_LEN; i++) {
    if (i < charsInBar) {
      printf("\033[1;%dm%c", color, PROGRESS_CHAR);
    } else {
      printf(" ");
    }
  }
  printf("\033[%dm] %d%% done\n",color, bar.prog);
}

void clearScreen() {
#ifdef _Win32
  system("cls");
#else
  system("clear");
#endif /* ifdef _Win32 */
}
