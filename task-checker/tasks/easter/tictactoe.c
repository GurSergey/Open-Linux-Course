/***
 MIT License

Copyright (c) 2017 Hitanshu Dhawan

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
#include <stdlib.h>

#define N 9

enum { O,X,EMPTY };

int HUMAN = 0;
int COMP = 1;

// initialize the borad with empty cells
void initBoardTicTac(int board[]) {

    for(int i=0; i<N; i++)
        board[i] = EMPTY;
}

// print the board on console
void printBoard(const int board[]) {

    char symbol[] = { 'O','X','-' };

    printf("\n  BOARD\n\n");
    for(int i=0; i<N; i++) {
        if(i != 0 && i%3 == 0)
            printf("\t  |  %d  %d  %d \n\n", i-2, i-1, i);
        printf(" %c ",symbol[board[i]]);
        if(i == N-1)
            printf("\t  |  %d  %d  %d \n\n", i-1, i, i+1);
    }
    printf("\n\n");
}

// checks if the board is full or not
// returns 1(true) if full
// returns 0(false) if even one cell is empty
int isBoardFull(const int board[]) {

    for(int i=0; i<N; i++)
        if(board[i] == EMPTY)
            return 0;
    return 1;
}

// makes a move on the given cell by given side
void makeMove(int board[], const int cell, const int side) {
    board[cell] = side;
}


// checks if a 3 is formed by a side
// returns 1 if yes
// returns 0 if no
int is3inARow(const int board[], const int side) {

    // horizontal
    if(board[0] == side && board[1] == side && board[2] == side)
        return 1;
    if(board[3] == side && board[4] == side && board[5] == side)
        return 1;
    if(board[6] == side && board[7] == side && board[8] == side)
        return 1;

    // vertical
    if(board[0] == side && board[3] == side && board[6] == side)
        return 1;
    if(board[1] == side && board[4] == side && board[7] == side)
        return 1;
    if(board[2] == side && board[5] == side && board[8] == side)
        return 1;

    // diagonal
    if(board[0] == side && board[4] == side && board[8] == side)
        return 1;
    if(board[2] == side && board[4] == side && board[6] == side)
        return 1;

    return 0;
}

// returns score for side
// +10 if particular side wins
// -10 if particular side loses
//  0 if draw or not yet complete
int isAWin(const int board[], const int side) {

    if(is3inARow(board,side))
        return 10;
    if(is3inARow(board,!side))
        return -10;
    return 0;
}

// returns which moves gives the maximum score
int max(int *scoreList,int moveCount,int *moveList,int *bestMove) {

    if(!moveCount)
        return 0;

    int max = -20;

    for(int i=0;i<moveCount;i++) {
        if(scoreList[i] > max) {
            max = scoreList[i];
            *bestMove = moveList[i];
        }
    }
    return max;
}

// returns which moves gives the minimum score
int min(int *scoreList,int moveCount,int *moveList,int *bestMove) {

    if(!moveCount)
        return 0;

    int min = +20;

    for(int i=0;i<moveCount;i++) {
        if(scoreList[i] < min) {
            min = scoreList[i];
            *bestMove = moveList[i];
        }
    }
    return min;
}

int minMax(int board[], int side, int *depth) {

    int moveList[N];
    int moveCount = 0;
    int bestMove;
    int scoreList[N];
    int bestScore;

    bestScore = isAWin(board,COMP);
    if(bestScore)
        return bestScore - *depth;

    // fill the moveList[]
    for(int i=0;i<N;i++) {
        if(board[i] == EMPTY)
            moveList[moveCount++] = i;
    }

    // loop through all moves
    int move;
    for(int i=0;i<moveCount;i++) {

        move = moveList[i];
        makeMove(board,move,side);

        (*depth)++;
        scoreList[i] = minMax(board,!side,depth);
        (*depth)--;

        makeMove(board,move,EMPTY);
    }

    if(side == COMP) {
        // MAX
        bestScore = max(scoreList,moveCount,moveList,&bestMove);
    }
    if(side == HUMAN) {
        // MIN
        bestScore = min(scoreList,moveCount,moveList,&bestMove);
    }

    if(*depth != 0)
        return bestScore;
    else
        return bestMove;
}

int getComputerMove(int *board,int side) {

    int depth = 0;
    int bestMove = minMax(board,side,&depth);
    printf("Searched.... bestMove: %d\n",bestMove+1);
    return bestMove;
}

int getHumanMove(const int *board) {

    printf("\nEnter your move !!\n\n");
    int move;
    while(1) {

        scanf("%d",&move);
        if(board[move-1] == EMPTY && move >=0 && move <=9)
            break;
        else
            printf("try again : ");
    }
    return move-1;
}

void runGame() {

    printf("\nChoose X or O. O moves first !!\n\n");
    while(1) {

        char choice = getchar();
        getchar();
        if(choice == 'O') {
            HUMAN = O;
            COMP = X;
            break;
        }
        if(choice == 'X') {
            HUMAN = X;
            COMP = O;
            break;
        }
        else {
            printf("Choose correct symbols\n");
        }
    }

    int gameOver = 0;
    int side = O;
    int move;
    int board[N];

    initBoardTicTac(board);
    printBoard(board);

    while(!gameOver) {

        if(side == HUMAN) {
            //Human Move
            move = getHumanMove(board);
            makeMove(board,move,side);
            printBoard(board);
        }
        else {
            //Computer Move
            move = getComputerMove(board,side);
            makeMove(board,move,side);
            printBoard(board);
        }


        //WIN
        if(is3inARow(board,side)) {
            printf("Game Over\n");
            gameOver = 1;
            if(side == COMP)
                printf("Computer Wins\n");
            else
                printf("Human Wins\n");
        }

        //DRAW
        if(isBoardFull(board)) {
            printf("Game Over\n");
            gameOver = 1;
            printf("It's a Draw\n");
        }

        side = !side;

    }
}

int main_tictactoe(int argc, char *argv[]) {

    runGame();

    return 0;
}