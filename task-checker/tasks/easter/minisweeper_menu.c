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
/**
 * menu.c
 * Version 1.0
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "minisweeper_def.h"



void runGameMinisweeper(struct block g[WIDTH][LENGTH]){
    int score = 0;
    bool won = false;
    //resets all blocks to unexposed
    reset(g);
    //generates mines
    generateMines(g);
    //displays blank grid for player to chose initial strike
    displayGrid(g);
    //get first input, first input will alwase have true as the boolean so the first entry will never hit a mine
    getInput(g, true);
    //displays initial grid
    displayGrid(g);
    while(!hasHitMine(g) && !hadWon(g)) {
        if(getInput(g, false)) {
            score++;
        }
        displayGrid(g);
        printf("Curent Score %d \n", score);
    }
    if(hadWon(g))
        won = true;
    exposeAll(g);
    displayGrid(g);
    if(won == true) {
        score+=100;
        printf("You Won! Your score is %d\n", score);
    }
    int choice;
    printf("Would you like to save your score? \n 1. Yes, \n 2. No\n: ");
    scanf("%d", &choice);
    if(choice == 1) {
        saveScores(score);
    }
    else
        printf("Your Final Score was %d\n", score);
}


void mainMenu(struct block g[WIDTH][LENGTH]){
    bool isDone = false;
    while(!isDone) {
        int choice = 0;
        printf("Shall we play a game?\n");
        printf("1. Yes\n");
        printf("2. View Past Scores\n");
        printf("3. Clear Past Scores\n");
        printf("4. Settings\n");
        printf("5. No/Quit \n");
        printf("Enter Menu Choice#: ");
        scanf(" %d", &choice);

        if(choice == 1)
            runGameMinisweeper(g);
        if(choice == 2)
            readScores();
        if(choice == 3)
            clearScores();
        if(choice == 3)
            clearScores();
        if(choice == 5)
            isDone = true;
    }
    exit(0);
}
