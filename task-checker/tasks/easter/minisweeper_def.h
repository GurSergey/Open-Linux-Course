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
#include <stdbool.h>

#ifndef SYMBOL
#define SYMBOL value

//will not take grids of more then 100 in LENGTH or WIDTH
#define WIDTH 20
#define LENGTH 20

//difficulty 3 easy, 2 middium, 1 hard
//difficulty algorithm is logrithem, in hard each block at a 50% chance of being mined, in middium 25% and in easy 12.5%
#define DIFFICULTY 3

//defines block
struct block {
    bool hasMine, exposed;
};


void displayGrid(struct block g[WIDTH][LENGTH]);
void generateMines(struct block g[WIDTH][LENGTH]);
void exposeAll(struct block g[WIDTH][LENGTH]);
bool hasHitMine(struct block g[WIDTH][LENGTH]);
bool getInput(struct block g[WIDTH][LENGTH], bool firstInput);
void reset(struct block g[WIDTH][LENGTH]);
bool hadWon(struct block g[WIDTH][LENGTH]);

void readScores();
void saveScores(int score);
void clearScores();

void mainMenu(struct block g[WIDTH][LENGTH]);



#endif

