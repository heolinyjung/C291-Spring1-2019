/* cell.c ---------
 *
 * Filename: cell.c
 * Description:
 * Author: Dmitrii Galantsev
 * Maintainer:
 * Created:      May 12 11:28 2018
 * Last-Updated: February 24 2019
 *           By: Heoliny Jung
 */

/* Commentary:
 *
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

/* Code: */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include "cell.h"

#define DRAW_CHAR '+'
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

cell_t * create_cell (int init_x, int init_y)
{
	// create the cell
    cell_t * c = malloc(sizeof(cell_t));
    c->x = init_x;
    c->y = init_y;
    c->draw_char = DRAW_CHAR;
    c->state[OLD] = UNKNOWN;
    c->state[CURRENT] = DIE;
    c->state[NEW] = UNKNOWN;

    return(c);
}

int destroy_cell (cell_t * c)
{
    free(c);

    return SUCCESS;
}

int update_cell (cell_t * c)
{
    c->state[OLD] = c->state[CURRENT];
    c->state[CURRENT] = c->state[NEW];
    c->state[NEW] = UNKNOWN;

    return SUCCESS;
}

// updates all of the cell states
void update_cells (int c_size_x, int c_size_y, cell_t * c[c_size_x][c_size_y])
{
    int x, y;
	for (x = 0; x < c_size_x; x++){
		for (y = 0; y < c_size_y; y++){
			update_cell(c[x][y]);
		}
	}
}

void print_cell (cell_t * c)
{
	printf("cell->x: %d\t cell->y: %d\t cell->draw_char %c\n", c->x, c->y, c->draw_char);
	printf("cell->state[0]: %d\t cell->state[1]: %d\t cell->state[2]: %d\n", c->state[OLD], c->state[CURRENT], c->state[NEW]);
}

void display_cell (cell_t * c)
{
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	if (c->state[CURRENT] == LIVE){
		attron(COLOR_PAIR(1));
		mvprintw(c->y, c->x,"%c", c->draw_char);
		attroff(COLOR_PAIR(1));
	}
	else{
		mvprintw(c->y, c->x, " ");
	}
}

// display all the cells
void display_cells (int c_size_x, int c_size_y, cell_t * c[c_size_x][c_size_y])
{
    int x, y;
	for (x = 0; x < c_size_x; x++){
		for (y = 0; y < c_size_y; y++){
			display_cell(c[x][y]);
		}
	}
}

// updates the NEW state in a given cell
void update_cell_state (cell_t * c,int neighbours)
{
	if (c->state[CURRENT] == LIVE) {
		if ((neighbours < 2)||(neighbours > 3)){
			c->state[NEW] = DIE;
		}
		else{
			c->state[NEW] = LIVE;
		}
	}
	else if ((c->state[CURRENT] == DIE) || (c->state[CURRENT] == UNKNOWN)) {
		if (neighbours == 3){
			c->state[NEW] = LIVE;
		}
		else{
			c->state[NEW] = DIE;
		}
	}
}

void undisplay_cell (cell_t * c)
{
    mvprintw(c->y, c->x, " ");
}

// count neighbours of each cell and update the state
// uses Oli's (my) new algorithim
//UPDATED TO USE TRANSPARENT WALLS
void update_neighbours (int c_size_x, int c_size_y, cell_t * c[c_size_x][c_size_y])
{
    int n;
    int x, y;
	for (x = 0; x < c_size_x-1; x++) {
		for (y = 0; y < c_size_y-1; y++) {
			n = 0; //num of neighbours
			int xmod;
			int ymod;
			int i;
			int j;
			for(i = -1; i <= 1; i++){
				for(j = -1; j <= 1; j++){
					if((x+i >= 0) && (x+i <= c_size_x) && (y+j >= 0) && (y+j <= c_size_y)){
						xmod = x+i;
						ymod = y+j;
					}
					else{
						if((x+i < 0) && (y+j >= 0) && (y+j <= c_size_y)){
							xmod = c_size_x + i;
							ymod = y+j;
						}
						if(x+i > c_size_x && (y+j >= 0) && (y+j <= c_size_y)){
							xmod = 0+i;
							ymod = y+j;
						}
						if(y+j < 0 && (x+i >= 0) && (x+i <= c_size_x)){
                                                        ymod = c_size_y-j;
							xmod = x+i;
                                                }
						if(y+j > c_size_y && (x+i >= 0) && (x+i <= c_size_x)){
                                                        ymod = 0+i;
							xmod = x+i;
                                                }
					}
					if(c[xmod][ymod]->state[CURRENT] == LIVE){
						n++;
					}
				}
			}
			n -= c[x][y]->state[CURRENT] == LIVE ? 1 : 0;
			update_cell_state(c[x][y],n);
		}
	}
}
