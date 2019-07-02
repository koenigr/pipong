#include <curses.h>

int main(int argc, char **argv)
{
  initscr();
  cbreak();
  printw("press any key to exit...");
  getch();
  endwin();
  return 0;
}