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
#include "minisweeper_def.h"


//topScores.txt


void readScores(){
    for(int i = 0; i < 30; i++)
        printf("\n");
    int scores;
    FILE* file = fopen("scores.txt", "r");

    if (!file) {
        printf("Missing Dependancys\n");
        exit(0);
    }
    // attempt to read the next line and store
    // the value in the "number" variable
    int no = 1;
    printf("Past Scores: \n");
    while (fscanf(file, "%d", &scores ) == true) {
        printf("     %d: %d \n", no, scores);
        no++;
    }
    fclose(file);
    printf("\n");

}



void saveScores(int score){
    FILE* file = fopen("scores.txt", "a");
    fprintf(file, "\n%d", score);
    fclose(file);
}


void clearScores(){
    FILE* file = fopen("scores.txt", "w");
    fclose(file);
}
