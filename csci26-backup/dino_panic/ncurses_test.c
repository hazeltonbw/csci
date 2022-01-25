//gcc ncurses_test.c -lncurses
#include <ncurses.h>

int main() {
  initscr(); cbreak();
  WINDOW *win = newwin(1,1, 1,1);
  for(int i=1; i < 16; ++i) {
    wresize(win, i, i);
    wclear(win);
    box(win, 0,0); // I've also tested wborder()
    wrefresh(win);
    mvprintw(0,0, "size: %i", i);
    getch(); //pause
  }
  endwin();
  return 0;
}
