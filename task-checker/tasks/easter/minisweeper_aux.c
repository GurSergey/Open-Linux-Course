/**
 MIT License

Copyright (c) 2019 Hunter Chasens

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "minisweeper_def.h"


bool hadWon(struct block g[WIDTH][LENGTH]){
    bool won = true;
    for(int y = 0; y < LENGTH; y++) {
        for(int x = 0; x < WIDTH; x++)
            //for evey block if the block does not have a mine and it is not exposed, sets won to false
            if(g[x][y].hasMine == false && g[x][y].exposed == false) {
                won = false;
            }
    }
    return won;
}

void reset(struct block g[WIDTH][LENGTH]){
    for(int y = 0; y < LENGTH; y++) {
        for(int x = 0; x < WIDTH; x++) {
            g[x][y].exposed=false;
        }
    }
}

bool hasHitMine(struct block g[WIDTH][LENGTH]){
    for(int y = 0; y < LENGTH; y++) {
        for(int x = 0; x < WIDTH; x++)
            if(g[x][y].hasMine == true && g[x][y].exposed) {
                return true;
            }
    }
    return false;
}

int suroundingMines(int x, int y, struct block g[WIDTH][LENGTH]){
    //produce a number of mines surounding
    int localNumOfMines = 0;
    int startY, stopY, startX, stopX;
    //sets start and stop to avoid a null pointer error
    //sets startX
    if(x<=0)
        startX = 0;
    else
        startX = x-1;
    //sets stopX
    if(x>=WIDTH-1)
        stopX = x;
    else
        stopX = x+1;
    //sets startY
    if(y<=0)
        startY = 0;
    else
        startY = y-1;
    //sets stopY
    if(y>=LENGTH-1)
        stopY = y;
    else
        stopY = y+1;

    for(int i = startY; i <= stopY; i++) {
        for(int j = startX; j <= stopX; j++) {
            if(g[j][i].hasMine == true)
                localNumOfMines++;
        }
    }

    return localNumOfMines;
}


/**
 * [clearEdge description]
 * @param x              [x location of block]
 * @param y              [y location of block]
 * @param [g]            [mine grid]
 * @param calledFromZero [set to false when called from outside of fuction]
 * this fuction is a recursive fuction, when calling from ouside alwase set calledFromZero to false;
 */
void clearEdge(int x, int y, struct block g[WIDTH][LENGTH], bool calledFromSelf){
    int startY, stopY, startX, stopX;
    //sets start and stop to avoid a null pointer error
    //sets startX
    if(x<=0)
        startX = 0;
    else
        startX = x-1;
    //sets stopX
    if(x>=WIDTH-1)
        stopX = x;
    else
        stopX = x+1;
    //sets startY
    if(y<=0)
        startY = 0;
    else
        startY = y-1;
    //sets stopY
    if(y>=LENGTH-1)
        stopY = y;
    else{
        stopY = y+1;
    }

    for(int i = startY; i <= stopY; i++) {
        for(int j = startX; j <= stopX; j++) {
            //if block is 0 and not exposed
            if(suroundingMines(j, i, g) == 0 && !g[j][i].exposed) {
                g[j][i].exposed = true;
                clearEdge(j, i, g, true);
            }
            if(calledFromSelf == true) {
                g[j][i].exposed = true;
            }
        }
    }
}

/**
 * [getInput: gets the input from user]
 * @param [2d array of struct bock g] [minesweeper grid]
 */
bool getInput(struct block g[WIDTH][LENGTH], bool firstInput){
    int x = -1, y = -1;
    while(x < 0 || x > WIDTH) {
        printf("Enter X: ");
        scanf(" %d", &x);
    }
    while(y < 0 || y > LENGTH) {
        printf("Enter Y: ");
        scanf(" %d", &y);
    }
    //makes it so that first input will never land on mine
    if(firstInput)
        g[x][y].hasMine = false;
    //returns true if the block has not been called on befor
    if (g[x][y].exposed != true && x < WIDTH && y < LENGTH) {
        g[x][y].exposed = true;
        clearEdge(x, y, g, false);
        return true;
    }
    //returns false if the block has been called on befor
    return false;
}

/**
 * generateMines: populates g with mines
 *
 */
void generateMines(struct block g[WIDTH][LENGTH]){
    srand(time(0));
    for(int y = 0; y < LENGTH; y++) {
        for(int x = 0; x < WIDTH; x++) {
            //50% chance of mine generation
            if(DIFFICULTY == 1)
                g[x][y].hasMine = (rand() & 1);
            //25% chance of mine generation
            if(DIFFICULTY == 2)
                g[x][y].hasMine = (rand() & 1) && (rand() & 1);
            //15% chance of mine generation
            if(DIFFICULTY == 3)
                g[x][y].hasMine = (rand() & 1) && (rand() & 1) && (rand() & 1);
        }
    }
}

/**
 * exposeAll: exposes all blocks
 *
 */
void exposeAll(struct block g[WIDTH][LENGTH]){
    for(int y = 0; y < LENGTH; y++) {
        for(int x = 0; x < WIDTH; x++) {
            g[x][y].exposed = true;
        }
    }

}






/**
 * displayGrid: will display the pass grid
 * untouched ground = #
 * dug ground = o
 * mines = x
 */
void displayGrid(struct block g[WIDTH][LENGTH]){
    //clears screen
    for(int i = 0; i < 30; i++)
        printf("\n");

    //prints X axis
    //add scalability for grids bigger then 10
    if(WIDTH > 10)
        printf("   ");
    else
        printf(" ");
    //ends scalability for x ais
    //displays x grid
    for(int x = 0; x < WIDTH; x++)
        //if width is biger then 10 then is scales for double digits
        //must scail seperatly single and double digits
        //scales for single digits here
        if(WIDTH > 10 && x < 10)
            printf(" %d ", x);
            //scales for double digits here
        else if(WIDTH > 10 && x >= 10)
            printf(" %d", x);
            //scales for grid under 10 in width
        else
            printf(" %d", x);
    printf("\n");

    //prints g (grid) and Y axis
    //start of Y axis labiling and scalable spacing for blocks
    for(int y = 0; y < LENGTH; y++) {
        printf("%d ", y);
        //gets the horizontal spaceing for blocks right for grids over 10
        if(LENGTH > 10 && y < 10)
            printf(" ");
        for(int x = 0; x < WIDTH; x++) {
            //gets the verticle spacing for blocks rigth for grids over 10
            if(WIDTH > 10)
                printf(" ");
            //end of Y axis labiling and scalable spacing for blocks
            //start of acual display
            //if block is exposed and has mine
            if ((g[x][y].exposed == true) && (g[x][y].hasMine == true)) {
                //add color red
                printf("\033[1;31m");
                printf("X");
                printf("\033[0m");
            }
            //if block is exposed has does not have mine
            if ((g[x][y].exposed == true) && (g[x][y].hasMine == false)) {
                //add color green
                printf("\033[0;32m");
                printf("%d", suroundingMines(x, y, g));
                printf("\033[0m");
            }
            //if block is not exposed
            if (g[x][y].exposed == false)
                printf("#");

            //prints out space for athestics
            printf(" ");
        }
        printf("\n");
    }
}
