/* game.c ---------
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

	well_t *w;

	int x_offset, y_offset;
	int wellW = WELL_WIDTH;
	int wellH = WELL_HEIGHT; //values for modifying well

	cell_t * cells[wellW-1][wellH-1];
	//cell_t * cellsPtr = cells;

	int x_max, y_max;
	int arrow;
	int move_counter = 0;
	int move_timeout = BASE_TIMEOUT;

	int test = 0;

	while(1) {
		switch(state) {
		case INIT:                   // Initialize the game, only run one time


			initscr();
			cbreak();
			noecho();                // Do not echo input characters
			getmaxyx(stdscr, y_max, x_max);  // Get the screen dimensions

			mvprintw(y_max-3,0,"Press '*' to increase speed by 1.2x");
			mvprintw(y_max-2,0,"Press '/' to decrease speed by 1.2x");
			mvprintw(y_max-5,0,"Press '+' to increase well size");
			mvprintw(y_max-4,0,"Press '-' to decrease well size");
			mvprintw(y_max-1,0,"Press 'q' to quit");

			x_offset = (x_max / 2) - (WELL_WIDTH / 2);
			y_offset = (y_max / 2) - (WELL_HEIGHT / 2);

            int i, j;
			for(i = 0; i < (WELL_WIDTH-1); i++){
				for(j = 0; j < (WELL_HEIGHT-1); j++){
					cells[i][j] = create_cell(x_offset + i, y_offset + j);
				}
			}

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
			nodelay(stdscr, TRUE); //don't wait for character enter on getch()
			mvprintw(y_max-1,20,"Current speed: %dms",move_timeout); //display current speed
			
			if (move_counter > move_timeout) {
				mvprintw(1, 50, "cells[6][6] state[old]:%d\n", cells[6][6]->state[OLD]);
				mvprintw(2, 50, "cells[6][6] state[current]:%d\n", cells[6][6]->state[CURRENT]);
				update_neighbours(WELL_WIDTH-1, WELL_HEIGHT-1, cells);
				mvprintw(3, 50, "cells[6][6] state[new]:%d\n", cells[6][6]->state[NEW]);
				update_cells(WELL_WIDTH-1, WELL_HEIGHT-1, cells);
				display_cells(WELL_WIDTH-1, WELL_HEIGHT-1, cells);
				cells[8+test][8+test]->state[CURRENT] = LIVE;
				move_counter = 0;
			}
			move_counter++;
			
			//get input during sim
			int input;
			input = getch();
			double tempMove;

			switch(input){
				case (int)'q':;
				case (int)'Q': state = EXIT;break; //exit condition
				
				//increase or decrease speed
				case (int)'*': tempMove = (double)move_timeout;tempMove /= 1.2;move_timeout = (int)tempMove;break;
				case (int)'/': tempMove = (double)move_timeout;tempMove *= 1.2;move_timeout = (int)tempMove;break;

				//increase or decrease well size
				case (int)'+': x_offset -= 1;wellW += 2;y_offset -= 1;wellH += 2;
					undraw_well(w);
					w = changeWellSize(x_offset-1,y_offset-1,wellW,wellH,w);
					draw_well(w);
					/*
					cell_t * cTemp[(int)wellW][(int)wellH];
					int i,j;
					for(i=0;i<wellW;i++){
						for(j=0;j<wellH;j++){
							if(i!=0&&j!=0&&i!=wellW-1&&j!=wellH-1){
								cTemp[i][j] = cells[i][j];
								undisplay_cell(cells[i][j]);
								destroy_cell(cells[i][j]);
							}
							else{
								cTemp[i][j] = create_cell(x_offset+i,y_offset+j);
							}
						}
					}
					*cellsPtr = cTemp;
					*/
					break;
				case (int)'-': x_offset += 1;wellW -= 2;y_offset += 1;wellH -= 2;
					undraw_well(w);
					w = changeWellSize(x_offset-1,y_offset-1,wellW,wellH,w);
					draw_well(w);
					/*
					cell_t * cNew[wellW][wellH];
					int i,j;
                                        for(i=0;i<wellW;i++){
                                                for(j=0;j<wellH;j++){
                                                        if(i!=1&&j!=1&&i!=wellW-2&&j!=wellH-2){
                                                                cNew[i][j] = cells[i][j];
								undisplay_cell(cells[i][j]);
                                                                destroy_cell(cells[i][j]);
                                                        }
                                                        else{
                                                                cNew[i][j] = create_cell(x_offset+i,y_offset+j);
                                                        }
                                                }
                                        }
                                        *cellsPtr = cNew;
					*/
					break;
				default:;
			}
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

//stop the program and clear the board
void end(){

	clear();
	endwin();
}
