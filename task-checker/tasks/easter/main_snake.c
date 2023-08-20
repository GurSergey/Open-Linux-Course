/**
MIT License

Copyright (c) 2020 Oualid BOUMAOUCHE

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

/* main.c */
#include "snake.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

/* constants =============================================================== */

/*
 * The height of the display area, in chars.
 * GRID_LINES chars for the game grid, one char for the game title,
 * another for the score.
 */
#define DISPLAY_HEIGHT GRID_LINES + 2

/*
 * The width of the display area, in chars.
 * Each column of the game grid, is represented by two characters, in width.
 */
#define DISPLAY_WIDTH  GRID_COLS * 2

#define FRAME_PER_SECOND 30

/* Microseconds per frame */
#define MICRO_PER_FRAME 1e3 / FRAME_PER_SECOND

#define GAME_TITLE "TermSnake"

#define GAME_OVER "Game Over"

enum colors {
    SNAKE_COLOR = 1,
    FOOD_COLOR,
    OBSTACLES_COLOR,
    POLICE_COLOR,
};

/* private functions ======================================================== */

static void render_cell(int y, int x)
{
    mvaddch(y, x, ' ');
    mvaddch(y, x + 1, ' ');
}

static void render_obstacles(int begin_line, int begin_col)
{
    int i;

    attron(COLOR_PAIR(OBSTACLES_COLOR));
    for (i = 0; i < OBSTACLES_COUNT; i++) {
        render_cell(begin_line + get_obstacles()[i].y,
                    begin_col + get_obstacles()[i].x * 2);
    }
    attroff(COLOR_PAIR(OBSTACLES_COLOR));
}

static void render_snake(int begin_line, int begin_col)
{
    int i;

    attron(COLOR_PAIR(SNAKE_COLOR));
    for (i = 0; i < get_snake_length(); i++) {
        render_cell(begin_line + get_snake()[i].y,
                    begin_col + get_snake()[i].x * 2);
    }
    attroff(COLOR_PAIR(SNAKE_COLOR));
}

static void render_food(int begin_line, int begin_col)
{
    attron(COLOR_PAIR(FOOD_COLOR));
    render_cell(begin_line + get_food().y, begin_col + get_food().x * 2);
    attroff(COLOR_PAIR(FOOD_COLOR));
}

static void render_information(int begin_line, int begin_col)
{
    attron(COLOR_PAIR(POLICE_COLOR));
    mvaddstr(begin_line - 1, begin_col, GAME_TITLE);
    mvprintw(begin_line + GRID_LINES, begin_col, "Score: %d", get_score());
    attroff(COLOR_PAIR(POLICE_COLOR));
}

static void render_game_over(void)
{
    attron(COLOR_PAIR(POLICE_COLOR));
    mvaddstr(LINES / 2, (COLS - strlen(GAME_OVER)) / 2, GAME_OVER);
    attroff(COLOR_PAIR(POLICE_COLOR));
}

static void render_game(void)
{
    int grid_begin_line, grid_begin_col;

    grid_begin_line = (LINES - GRID_LINES) / 2;
    grid_begin_col = (COLS - GRID_COLS * 2) / 2;

    erase();
    render_obstacles(grid_begin_line, grid_begin_col);
    render_snake(grid_begin_line, grid_begin_col);
    render_food(grid_begin_line, grid_begin_col);
    render_information(grid_begin_line, grid_begin_col);
    refresh();
}

static void init_graphics(void)
{
    if (initscr() == NULL) {
        exit(EXIT_FAILURE);
    }
    if (start_color() == ERR) {
        fputs("Error: error when starting color mode", stderr);
        endwin();
        exit(EXIT_FAILURE);
    }
    if (LINES < DISPLAY_HEIGHT || COLS < DISPLAY_WIDTH) {
        fprintf(stderr,
                "Error: the terminal must be at least %d characters "
                "high, and %d characters wide\n", DISPLAY_HEIGHT,
                DISPLAY_WIDTH);
        endwin();
        exit(EXIT_FAILURE);
    }
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    init_pair(SNAKE_COLOR, COLOR_WHITE, COLOR_GREEN);
    init_pair(FOOD_COLOR, COLOR_WHITE, COLOR_RED);
    init_pair(OBSTACLES_COLOR, COLOR_WHITE, COLOR_CYAN);
    init_pair(POLICE_COLOR, COLOR_WHITE, COLOR_BLACK);
}

/* entry points ============================================================= */

void main_snake(void)
{
    int quit;
    clock_t previous;
    double lag;

    init_graphics();
    init_game();
    quit = 0;
    previous = clock();
    lag = 0.0;

    while (!quit) {
        clock_t current;
        double elapsed;
        double speed;

        /*
         * Calculate the duration of the last loop execution,
         * then add it to lag.
         */
        current = clock();
        elapsed = ((double) (current - previous) / CLOCKS_PER_SEC) * 1e3;
        previous = current;
        lag += elapsed;

        switch (getch()) {
            case KEY_LEFT:
                turn_left();
                break;
            case KEY_RIGHT:
                turn_right();
                break;
            case KEY_UP:
                turn_up();
                break;
            case KEY_DOWN:
                turn_down();
                break;
            case 'q':
            case 'Q':
                quit = 1;
                break;
        }

        /*
         * If the lag is greater than or equal to the game update interval,
         * update it.
         */
        while (lag >= (speed = get_speed())) {
            /* Update_game returns a non 0 value if the game is over */
            if (update_game()) {
                render_game_over();
                nodelay(stdscr, FALSE);
                getch();
                quit = 1;
            }
            lag -= speed;
        }

        render_game();
    }

    endwin();
    exit(EXIT_SUCCESS);
}
