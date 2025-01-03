#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int getFormat();
void clearScreen();
void getDate(char *); // we can only do this in code, uunfortunately :(
void getTime(char *, int);

int main() {
  int format = getFormat();
  char dateBuffer[120], timeBuffer[80];

  while (1) {
    clearScreen();
    getDate(dateBuffer);
    getTime(timeBuffer, format);
    printf("Current date: %s\n", dateBuffer);
    printf("Current time: %s\n", timeBuffer);

    sleep(1);
  }
  return 0;
}

int getFormat() {
  int format;
  printf("1. 24-Hour format (00:00:00)\n2. 12-Hour format (12:00:00 AM)\n");
  printf("Select format: ");
  scanf("%d", &format);

  if (format != 1 || format != 2) {
    printf("Enter valid format: ");
    scanf("%d", &format);
  }

  /* if (scanf("%d", &format) != 1 || (format != 1 && format != 2)) {
     format = 1;
   } */
  return format;
}

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void getDate(char *buf) {
  time_t rawTime;
  struct tm *fullCurrentTime;

  time(&rawTime);
  fullCurrentTime = localtime(&rawTime);
  strftime(buf, 80, "%A, %B %d %Y", fullCurrentTime);
}

void getTime(char *buf, int format) {
  time_t rawTime;
  struct tm *fullCurrentTime;

  time(&rawTime);
  fullCurrentTime = localtime(&rawTime);
  if (format == 1) {
    strftime(buf, 120, "%H:%M:%S", fullCurrentTime);
  } else {
    strftime(buf, 120, "%I:%M:%S %p", fullCurrentTime);
  }
};
