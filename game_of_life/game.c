/* game.c -------
 *
 * Filename: game.c
 * Description:
 * Author: Dmitrii Galantsev
 * Maintainer:
 * Created:      May 12 11:28 2018
 * Last-Updated: September 23 15:38 2018
 *           By: Dmitrii Galantsev
 */

/* Commentary:
 *
 *
 */

/* Copyright (c) 2018 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "cell.h"
#include "game.h"
#include "well.h"
#include "key.h"

void init_game(void)
{
	int x,y;
}

int game(void)
{
	static int state = INIT;
	struct timespec tim = {0,1000000};  // Each execution of while(1) is approximately 1mS
	struct timespec tim_ret;

	cell_t * cells[WELL_WIDTH-1][WELL_HEIGHT-1];

	well_t *w;

	int x_offset, y_offset;
	int x_max, y_max;
	int arrow;
	int move_counter = 0;
	int move_timeout = BASE_TIMEOUT;

	int test = 0;

	while(1) {
		switch(state) {
		case INIT:                   // Initialize the game, only run one time


			initscr();
			nodelay(stdscr, TRUE);   // Do not wait for characters using getch.
			noecho();                // Do not echo input characters
			getmaxyx(stdscr, y_max, x_max);  // Get the screen dimensions

			x_offset = (x_max / 2) - (WELL_WIDTH / 2);
			y_offset = (y_max / 2) - (WELL_HEIGHT / 2);

            int i, j;
			for(i = 0; i < (WELL_WIDTH-1); i++)
				for(j = 0; j < (WELL_HEIGHT-1); j++)
					cells[i][j] = create_cell(x_offset + i, y_offset + j);

            // still life
			cells[5][5]->state[CURRENT] = LIVE;
			cells[5][6]->state[CURRENT] = LIVE;
			cells[6][5]->state[CURRENT] = LIVE;
			cells[6][6]->state[CURRENT] = LIVE;

            // glider
			cells[20][5]->state[CURRENT] = LIVE;
			cells[20][6]->state[CURRENT] = LIVE;
			cells[20][7]->state[CURRENT] = LIVE;
			cells[21][7]->state[CURRENT] = LIVE;
			cells[22][6]->state[CURRENT] = LIVE;

            // oscillator
			cells[20][20]->state[CURRENT] = LIVE;
			cells[20][21]->state[CURRENT] = LIVE;
			cells[20][22]->state[CURRENT] = LIVE;

			//cells[22][20]->state[CURRENT] = LIVE;
			//cells[23][20]->state[CURRENT] = LIVE;
			//cells[23][18]->state[CURRENT] = LIVE;
			//cells[25][19]->state[CURRENT] = LIVE;
			//cells[26][20]->state[CURRENT] = LIVE;
			//cells[27][20]->state[CURRENT] = LIVE;
			//cells[28][20]->state[CURRENT] = LIVE;


			w = init_well(x_offset - 1, y_offset - 1, WELL_WIDTH, WELL_HEIGHT);
			draw_well(w);

			state = STEP;
			break;
		case STEP:
			if (move_counter > move_timeout) {
				mvprintw(1, 50, "cells[6][6] state[old]:%d\n", cells[6][6]->state[OLD]);
				mvprintw(2, 50, "cells[6][6] state[current]:%d\n", cells[6][6]->state[CURRENT]);
				update_neighbours(WELL_WIDTH - 1, WELL_HEIGHT - 1, cells);
				mvprintw(3, 50, "cells[6][6] state[new]:%d\n", cells[6][6]->state[NEW]);
				update_cells(WELL_WIDTH - 1, WELL_HEIGHT - 1, cells);
				display_cells(WELL_WIDTH - 1, WELL_HEIGHT - 1, cells);
				//cells[8+test][8+test]->state[CURRENT] = LIVE;
				move_counter = 0;
			}
			move_counter++;

			// TODO: Figure out if this works VVVVV
			//update_cells(WELL_WIDTH - 2, WELL_HEIGHT - 2, cells);
			break;
		case EXIT:
			end();
			return(0);
			break;
		}
		refresh();
		nanosleep(&tim,&tim_ret);
	}
}
