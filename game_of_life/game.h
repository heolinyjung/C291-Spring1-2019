/* game.h ---------
 *
 * Filename: game.h
 * Description:
 * Author: Dmitrii Galantsev
 * Maintainer:
 * Created:      May 12 11:28 2018
 * Last-Updated: September 23 15:38 2018
 *           By: Dmitrii Galantsev
 */

/* Commentary:
 *
 */

/* Copyright (c) 2018 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

typedef struct terminal_dimensions
{
  int maxx;
  int maxy;
} terminal_dimensions_t;

// Delay timers for the main game loop.
#ifndef DELAY_US
#define DELAY_US 100000
#define BASE_TIMEOUT 150 //changed to 150ms
#endif

// Game States
enum {INIT, STEP, GAME_OVER, EXIT};

void init_game(void);
void end(int,int);
int game(int);
void saveBoard(cell_t ***,int,int,int,int);
void changeBoardSize(cell_t ***,int);

/* game.h ends here */
