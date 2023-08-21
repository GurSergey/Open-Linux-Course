
#include <stdio.h>
#include <stdlib.h>
#include "2048.h"
#include "cmatrix.h"
#include "tictactoe.h"
#include "main_blackjack.h"
#include "minisweeper.h"
#include "tetris.h"
#include "main_snake.h"

void run_easter() {
    printf("\n\nYou found easter eggs page!!!\n"
           "         .-\"-.\n"
           "       .'=^=^='.\n"
           "      /=^=^=^=^=\\\n"
           "     :^=EASTER =^;\n"
           "     |^   EGG ! ^|\n"
           "     :^=^=^=^=^=^:\n"
           "      \\=^=^=^=^=/\n"
           "       `.=^=^=.'\n"
           "         `~~~`\n");

    printf("You must answering on secret riddle, if you want to open easter eggs \n");
    printf("Type your answer on this riddle:\n");
    printf("Riddle 1: Wake up Neo... The Matrix has you... \n");
    printf("Riddle 2: 2^11 = ? \n");
    printf("Riddle 3: FTP port ? \n");

    printf("Riddle 4: Age of Unix ? \n");
    printf("Riddle 5: Ultimate Question of Life, the Universe, and Everything?\n");
    //    printf("Riddle 6: 5 8 13 21 ? \n");
//    printf("Riddle 7: Golden ratio = 2sin(x) ?  \n");
    printf("Type answer: \n");
    long num;
    char num_array[10];
    scanf("%s", num_array);
    num = strtol(num_array, NULL, 10);
    switch (num) {
        case 1999:
            main_matrix(1, NULL);
            break;
        case 2048:
            main_2048(1, NULL);
            break;
        case 21:
            main_blackjack(1, NULL);
            break;
//        case 54:
//            main_tictactoe(1, NULL);
//            break;
//        case 34:
//            main_minisweeper();
//            break;
        case 1970:
            main_tetris();
            break;
        case 42:
            main_snake();

            break;
        default:
            printf("Wrong answer...\n Try Again");
            break;
    }

}