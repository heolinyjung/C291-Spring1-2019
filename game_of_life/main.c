/*main.c ---------
 *
 * Filename: main.c
 * Description:
 * Author: Bryce Himebaugh
 * Maintainer:
 * Created: Thu Aug 18 16:32:20 2017
 * Last-Updated: February 24 2019
 *           By: Heoliny Jung
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 *
 *
 */

/* Copyright (c) 2004-2007 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

/* Code: */
#include <stdio.h>
#include <ncurses.h>
#include "cell.h"
#include "game.h"
#include "key.h"

int main(void)
{
  int y_max,x_max;
  initscr();
  cbreak();
  noecho();                // Do not echo input characters
  getmaxyx(stdscr, y_max, x_max);  // Get the screen dimensions
  int shape;
  int input;
  mvprintw(y_max/2,(x_max/2)-10,"Welcome to Oli's Game Of Life!");
  mvprintw((y_max/2)+1,(x_max/2)-10,"Choose a starting shape:");
  mvprintw((y_max/2)+2,(x_max/2)-10,"1. Still Life");
  mvprintw((y_max/2)+3,(x_max/2)-10,"2. Glider");
  mvprintw((y_max/2)+4,(x_max/2)-10,"3. Oscillator");
  mvprintw((y_max/2)+5,(x_max/2)-10,"4. Random 3x3 shape");
  while(shape != (int)'1' && shape != (int)'2' && shape != (int)'3' && shape != (int)'4'){
   shape = getch();
  }
  mvprintw((y_max/2)+6,(x_max/2)-10,"Press 's' to start");
  while(input != (int)'s' && input !='S'){
    input = getch();
  }
  endwin();
  game(shape);
  return (0);
}
