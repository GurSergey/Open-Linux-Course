/**
 * Assignemnt 3: Minesweeper
 * Authors: Hunter Chasens and
 * Version: Alpha 1.0
 *
 * This is a CLI Minesweeper game, you input the cordanates,
 *
 *
 * Discription of a block:
 *        blocks are the structure that make up grid
 *        each block contains its cordanates, in 'x' and 'y' intagers
 *        and two boolean values, 'hasMine' and 'exposed'
 *
 *
 * Discription of grid:
 *        grid is the land of Minesweeper
 *        a grid is a two dimetional array of blocks
 *
 *
 * Algorithm:
 * (preprocessor)
 *
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
#include <math.h>
#include "minisweeper_def.h"


//Start of Member Field
//main minesweeper feild
struct block grid[WIDTH][LENGTH];

//auxilerary structure used for

//End of Member Field


int main_minisweeper(){
    mainMenu(grid);
    return 0;
}
