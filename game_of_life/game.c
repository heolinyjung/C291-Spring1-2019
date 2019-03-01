/* game.c ---------
 *
 * Filename: game.c
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
#include <stdlib.h>
#include "cell.h"
#include "game.h"
#include "well.h"
#include "key.h"

void init_game(void)
{
	int x,y;
}

int game(int shape)
{
	static int state = INIT;
	struct timespec tim = {0,1000000};  // Each execution of while(1) is approximately 1mS
	struct timespec tim_ret;
	srand(time(NULL));

	well_t *w;

	int x_offset, y_offset;
	int wellW = WELL_WIDTH;
	int wellH = WELL_HEIGHT; //values for modifying well

	cell_t * cells[wellW-1][wellH-1];
	cell_t *** cellsPtr = cells;

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
			mvprintw(y_max-6,0,"Press 'p' to pause/unpause the simulation");
			mvprintw(y_max-1,0,"Press 'q' to quit");

			x_offset = (x_max / 2) - (WELL_WIDTH / 2);
			y_offset = (y_max / 2) - (WELL_HEIGHT / 2);

            		int i, j;
			for(i = 0; i < (WELL_WIDTH-1); i++){
				for(j = 0; j < (WELL_HEIGHT-1); j++){
					cells[i][j] = create_cell(x_offset + i, y_offset + j);
				}
			}

			mvprintw(y_max-9,0,"shape number %c",'1');
			mvprintw(y_max-10,0,"shape number %d",shape);
			switch(shape){
            			case (int)'1':// still life
					cells[5][5]->state[CURRENT] = LIVE;
					cells[5][6]->state[CURRENT] = LIVE;
					cells[6][5]->state[CURRENT] = LIVE;
					cells[6][6]->state[CURRENT] = LIVE;
					break;
            			case (int)'2':// glider
					cells[20][5]->state[CURRENT] = LIVE;
					cells[20][6]->state[CURRENT] = LIVE;
					cells[20][7]->state[CURRENT] = LIVE;
					cells[21][7]->state[CURRENT] = LIVE;
					cells[22][6]->state[CURRENT] = LIVE;
					break;
		            	case (int)'3':// oscillator
					cells[20][20]->state[CURRENT] = LIVE;
					cells[20][21]->state[CURRENT] = LIVE;
					cells[20][22]->state[CURRENT] = LIVE;
					break;
				case (int)'4':// random 3x3
					for(i = 0; i<3; i++){
						for(j = 0; j<3; j++){
							int r = rand(); //generate random num and use %2 to get a 1 or 0;
							cells[15+i][15+j]->state[CURRENT] = (r%2 == 1) ? LIVE:DIE;
						}
					}
					break;
				default:;
			}

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
				case (int)'Q': state = GAME_OVER;break; //exit condition
				case (int)'p':;
				case (int)'P': input = getch();
					while(input!=(int)'P' && input!=(int)'p'){
						input = getch();
					}
					break;
				//increase or decrease speed
				case (int)'*': tempMove = (double)move_timeout;tempMove /= 1.2;move_timeout = (int)tempMove;break;
				case (int)'/': tempMove = (double)move_timeout;tempMove *= 1.2;move_timeout = (int)tempMove;break;

				//increase or decrease well size
				case (int)'+': x_offset -= 1;wellW += 2;y_offset -= 1;wellH += 2;
					undraw_well(w);
					w = changeWellSize(x_offset-1,y_offset-1,wellW,wellH,w);
					draw_well(w);
					break;
				case (int)'-': x_offset += 1;wellW -= 2;y_offset += 1;wellH -= 2;
					undraw_well(w);
					w = changeWellSize(x_offset-1,y_offset-1,wellW,wellH,w);
					draw_well(w);
					changeBoardSize(cellsPtr,);
					break;
				case (int)'r':;
				case (int)'R':
                                        for(i=1;i<wellW-1;i++){
                                                for(j=1;j<wellH-1;j++){
							cells[i][j]->state[CURRENT] = DIE;
							cells[i][j]->state[NEW] = DIE;
                                                }
                                        }break;
				case (int)'F':;
				case (int)'f':
					//saveBoard(cells,x-offset,y-offset,wellW,wellH);
					break;
				case (int)'L':;
				case (int)'l':;
					/*FILE *savePtr;
					char fileName[20];
					int num;
					scanw("%d",&num);
					sprintf(fileName,"./saves/save%d.dat\0",num);
                                        if((boardFPtr = fopen(fileName,"r")) == NULL){
                                                mvprintw(5,0,"Save file %d could not be created",saveNum);
                                        }
                                        else{
						int xpos,ypos;
						fscanf("%d\n%d\n%d\n%d\n",&xpos,&ypos,&wellW,&wellH);
						x_offset = xpos;
						y_offest = ypos;
						for(i = 0; i<wellW-1; i++){
							for(j = 0; j < wellH-1; j++){
								int stat;
								fscanf("%*d %*d %d\n",stat);
                                                                if(stat == 1){
									cells[i][j]->status[CURRENT] = LIVE;
								}
								else{
									cells[i][j]->status[CURRENT] = DIE;
								}
                                                        }
						}
						fclose(savePtr);
					}*/break;
				default:;
			}
			break;
		case GAME_OVER: 
			end(x_max,y_max);
			state = EXIT;
			break;

		case EXIT:
			clear();
			endwin();
			return(0);
			break;
		}
		refresh();
		nanosleep(&tim,&tim_ret);
	}
}

//stop the program and clear the board
void end(int x_max, int y_max){
	clear();
	mvprintw(y_max/2,(x_max/2)-30,"All life has been terminated. Why did you have to do this?...(Press any key to exit)");
	nodelay(stdscr, FALSE);
	int cont = getch();
	if(cont){}
}

void changeBoardSize(cell_t ***, int change){
	cell_t * cNew[wellW][wellH];
        for(i=0;i<wellW;i++){
        	for(j=0;j<wellH;j++){
                	if(i!=change&&j!=1&&i!=wellW-1&&j!=wellH-1){
                        	cNew[i][j] = cells[i][j];
                                                                undisplay_cell(cells[i][j]);
                                                                destroy_cell(cells[i][j]);
                                                        }
                                                        else{
                                                                cNew[i][j] = create_cell(x_offset+i,y_offset+j);
                                                        }
                                                }
                                        }
                                        cells = cNew;
}

//save a board to a file
/*
 * Files are formatted like so:
 * WellX
 * WellY
 * WellW
 * WellH
 * cellX cellY cellState[CURRENT]
 * ...
 * EOF
 * MOVED TO INSIDE MAIN
void saveBoard(cell_t ** cells, int wellX, int wellY, int wellW, int wellH){
	FILE *tempPtr;
	if((tempPtr = fopen("./saves/temp.txt","w")) == NULL){
                mvprintw(5,0,"Temp not be opened");
        }
        else{
                fprintf(tempPtr,"Text");
                mvprintw(5,0,"Text");
                fclose(tempPtr);
        }

	FILE *countPtr;
	int saveNum;
	if((countPtr = fopen("./saves/numSaves.txt","r")) == NULL){
		mvprintw(5,0,"Number of saves file could not be opened");
	}
	else{
		fscanf(countPtr,"%d",&saveNum);
		mvprintw(5,0,"%d",saveNum);
		fclose(countPtr);
	}
	FILE *boardFPtr;
	char fileName[20];
	sprintf(fileName,"./saves/save%d.dat\0",saveNum);
	mvprintw(5,0,"%s",fileName);
	if((boardFPtr = fopen(fileName,"w")) == NULL){
		mvprintw(5,0,"Save file %d could not be created",saveNum);
	}
	else{
		fprintf(boardFPtr,"%d\n%d\n%d\n%d\n",wellX,wellY,wellH,wellW);
		int i,j;
		mvprintw(8,0,"%d",cells[5][5]->state[CURRENT]==LIVE?1:0);
		for(i = 0; i<WELL_WIDTH-1;i++){
			for(j = 0; j<WELL_HEIGHT-1; j++){
				int cState = (cells[i][j])->state[CURRENT] == LIVE ? 1:0;
				fprintf(boardFPtr,"%d %d %d\n",i,j,cState);
			}
		}
		fclose(boardFPtr);
	}

}
*/
