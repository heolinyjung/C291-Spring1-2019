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
#include <curses.h>
#include <menu.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "cell.h"
#include "game.h"
#include "well.h"
#include "key.h"

char *choices[] = {
                "Resume",
                "Reset",
                "Place a new shape",
                "Help!",
                "Quit",
		(char*)NULL
};

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
			mvprintw(y_max-6,0,"Press 'p' to pause and bring up the menu");
			mvprintw(y_max-7,0,"Press 'g' for a secret!");

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
			int menu;

			switch(input){
				case (int)'p':;
				case (int)'P':
					state = PAUSED;
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
					//changeBoardSize(cellsPtr,);
					break;
				case (int)'g':
					nodelay(stdscr,FALSE);
					for(i=1;i<wellW-1;i++){
                                                for(j=1;j<wellH-1;j++){
                                                         cells[i][j]->state[CURRENT] = DIE;
                                                         cells[i][j]->state[NEW] = DIE;
                                                }
                                        }
					//G
					cells[2][2]->state[CURRENT] = LIVE;
                                        cells[3][2]->state[CURRENT] = LIVE;
                                        cells[4][2]->state[CURRENT] = LIVE;
                                        cells[5][2]->state[CURRENT] = LIVE;
					cells[6][2]->state[CURRENT] = LIVE;
                                        cells[2][3]->state[CURRENT] = LIVE;
                                        cells[2][4]->state[CURRENT] = LIVE;
                                        cells[2][5]->state[CURRENT] = LIVE;
                                        cells[2][6]->state[CURRENT] = LIVE;
					cells[3][6]->state[CURRENT] = LIVE;
                                        cells[4][6]->state[CURRENT] = LIVE;
                                        cells[5][6]->state[CURRENT] = LIVE;
                                        cells[6][6]->state[CURRENT] = LIVE;
					cells[6][4]->state[CURRENT] = LIVE;
                                        cells[6][5]->state[CURRENT] = LIVE;
					cells[5][4]->state[CURRENT] = LIVE;
                                        cells[4][4]->state[CURRENT] = LIVE;

					//N
                                        cells[8][2]->state[CURRENT] = LIVE;
                                        cells[8][3]->state[CURRENT] = LIVE;
                                        cells[8][4]->state[CURRENT] = LIVE;
					cells[8][5]->state[CURRENT] = LIVE;
					cells[8][6]->state[CURRENT] = LIVE;
					cells[9][3]->state[CURRENT] = LIVE;
					cells[10][4]->state[CURRENT] = LIVE;
					cells[11][5]->state[CURRENT] = LIVE;
					cells[12][6]->state[CURRENT] = LIVE;
					cells[12][2]->state[CURRENT] = LIVE;
                                        cells[12][3]->state[CURRENT] = LIVE;
                                        cells[12][4]->state[CURRENT] = LIVE;
                                        cells[12][5]->state[CURRENT] = LIVE;

					//U
					cells[14][2]->state[CURRENT] = LIVE;
                                        cells[14][3]->state[CURRENT] = LIVE;
                                        cells[14][4]->state[CURRENT] = LIVE;
                                        cells[14][5]->state[CURRENT] = LIVE;
                                        cells[14][6]->state[CURRENT] = LIVE;
					cells[15][6]->state[CURRENT] = LIVE;
                                        cells[16][6]->state[CURRENT] = LIVE;
                                        cells[17][6]->state[CURRENT] = LIVE;
                                        cells[18][6]->state[CURRENT] = LIVE;
					cells[18][2]->state[CURRENT] = LIVE;
                                        cells[18][3]->state[CURRENT] = LIVE;
                                        cells[18][4]->state[CURRENT] = LIVE;
                                        cells[18][5]->state[CURRENT] = LIVE;
                                        cells[18][6]->state[CURRENT] = LIVE;
					display_cells(WELL_WIDTH-1, WELL_HEIGHT-1, cells);
					mvprintw(y_max-1,20,"Press any button to continue");
					input = getch();
					break;
				default:;
			}
			break;
		case PAUSED:
			menu = pauseGame(x_max,y_max);
                        switch(menu){
                        //Reset = 1, new shape = 2, help = 3, quit = 4
                        	case 1:
                                	for(i=1;i<wellW-1;i++){
                                        	for(j=1;j<wellH-1;j++){
                                                	cells[i][j]->state[CURRENT] = DIE;
                                                        cells[i][j]->state[NEW] = DIE;
                                                }
                                        }break;
                                case 2:mvprintw(y_max-10,0,"New shape");
                                	break;
                                case 3:mvprintw(y_max-10,0,"Help");
                                	break;
                                case 4:
                                	state = GAME_OVER;
                                        break;
                                default:mvprintw(20,0,"%d",menu);
                        }
                        draw_well(w);
                        mvprintw(y_max-3,0,"Press '*' to increase speed by 1.2x");
                        mvprintw(y_max-2,0,"Press '/' to decrease speed by 1.2x");
                        mvprintw(y_max-5,0,"Press '+' to increase well size");
                        mvprintw(y_max-4,0,"Press '-' to decrease well size");
                        mvprintw(y_max-6,0,"Press 'p' to pause and bring up the menu");
			state = STEP;
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
/*
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

void loadBoard(cell_t *** cTemp, int wellX, int wellY, int wellW, int wellH){
	FILE *savePtr;
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
        }
}
*/

//Menu gen
int pauseGame(int x_max, int y_max){
	nodelay(stdscr,FALSE);
	ITEM **menuItems;
	int c;
	MENU *menuPtr;
	WINDOW* menuWindow;
	int numChoices, i;
	ITEM *currentItem;

	// Initialize
	clear();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr,TRUE);
	init_pair(1, COLOR_BLUE, COLOR_WHITE);

	// Create items
	numChoices = ARRAY_SIZE(choices);
	menuItems = (ITEM**)calloc(numChoices + 1, sizeof(ITEM*));

	for(i = 0; i < numChoices; ++i){
		menuItems[i] = new_item(choices[i],choices[i]);
	}
	menuItems[numChoices] = (ITEM*)NULL;

	// Initialize menu
	menuPtr = new_menu((ITEM**)menuItems);

	menuWindow = newwin(10,27,(y_max/2) - 5,(x_max/2) - 10);
	keypad(menuWindow,TRUE);

	set_menu_win(menuPtr, menuWindow);
	set_menu_sub(menuPtr, derwin(menuWindow,6,20,3,1));

	// Sets marker to *
	set_menu_mark(menuPtr, " * ");

	print_in_middle(menuWindow, 1, 0, 27, "Oli's Game Of Life Menu", COLOR_PAIR(1));
	mvwaddch(menuWindow, 2, 0, (int)'|');
	mvwhline(menuWindow, 2, 1, (int)'-', 25);
	mvwaddch(menuWindow, 2, 26, (int)'|');

	refresh();
	post_menu(menuPtr);
	wrefresh(menuWindow);

	//ATTEMPT
	char* reset = "Reset";
	char* exit = "Quit";

	//output int
	int out = 0;
	while((c = getch()) != 10){
		
		switch(c){
			case KEY_DOWN:
				menu_driver(menuPtr, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(menuPtr, REQ_UP_ITEM);
				break;
			case 10: /* Enter */
				if(strcmp(item_name(current_item(menuPtr)),"Resume")==0)
                                        out = 5;	
				else if(strcmp(item_name(current_item(menuPtr)),"Reset")==0)
					out = 1;
				else if(strcmp(item_name(current_item(menuPtr)),"Place a new shape")==0)
                                        out = 2;
				else if(strcmp(item_name(current_item(menuPtr)),"Help!")==0)
                                        out = 3;
				else if(strcmp(item_name(current_item(menuPtr)),exit)==0)
                                        out = 4;
				break;
		}
		refresh();
	}

	unpost_menu(menuPtr);
	free_menu(menuPtr);
	for(i = 0; i < numChoices; ++i){
		free_item(menuItems[i]);
	}
	clear();
	return out;
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}
