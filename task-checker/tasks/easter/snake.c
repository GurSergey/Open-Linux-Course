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

 *
 */

/* snake.c */
#include <stdlib.h>
#include <time.h>
#include "snake.h"

/* constants ================================================================ */

#define SNAKE_INIT_LEN  4

#define SNAKE_MAX_LEN   GRID_LINES * GRID_COLS

/*
 * The speed represents the time interval to update the game, in milliseconds
 */
#define INIT_SPEED      500

#define SPEED_CHANGE    10

#define MAX_SPEED       100

#define SCORE_CHANGE    100

enum direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

/* private variables ======================================================== */

static Cell snake[SNAKE_MAX_LEN];

static Cell obstacles[OBSTACLES_COUNT];

static int snake_length;

static enum direction direction;

static int speed;

static Cell food;

static int scoreSnake;

static int updated;

static int over;

/* private functions ======================================================== */

static void init_obstacles(void)
{
    int x, y, i;

    i = 0;
    /* initialize the left side obstacles */
    for (y = 0; y < GRID_LINES; y++) {
        obstacles[i].y = y;
        obstacles[i++].x = 0;
    }
    /* initialize the right side obstacles */
    for (y = 0; y < GRID_LINES; y++) {
        obstacles[i].y = y;
        obstacles[i++].x = GRID_COLS - 1;
    }
    /* initialize the top side obstacles */
    for (x = 0; x < GRID_COLS; x++) {
        obstacles[i].y = 0;
        obstacles[i++].x = x;
    }
    /* initialize the bottom side obstacles */
    for (x = 0; x < GRID_COLS; x++) {
        obstacles[i].y = GRID_LINES - 1;
        obstacles[i++].x = x;
    }
}

static int are_equal_cells(Cell cell1, Cell cell2)
{
    return (cell1.y == cell2.y) && (cell1.x == cell2.x);
}

/*
 * function: is_colliding
 * ----------------------
 * determine if a cell is colliding the obstacles (obstacles + snake)
 *
 * cell: the cell for which we check whether it is colliding the obstacles
 * head: if it is 0, then the snake head is not considered as an obstacle
 *
 * returns: 1 if the cell is colliding an obstacle (obstacles or snake),
 * 0 otherwise
 */
static int is_colliding(Cell cell, int head)
{
    int i;

    for (i = head ? 0 : 1; i < snake_length; i++) {
        if (are_equal_cells(cell, snake[i])) {
            return 1;
        }
    }
    for (i = 0; i < OBSTACLES_COUNT; i++) {
        if (are_equal_cells(cell, obstacles[i])) {
            return 1;
        }
    }
    return 0;
}

static void generate_food(void)
{
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    do {
        food.y = rand() % GRID_LINES;
        food.x = rand() % GRID_COLS;
        /* while the food is generated within the obstacles or the snake */
    } while (is_colliding(food, 1));
}

/* entry points ============================================================= */

/*
 * function: init_game
 * -------------------
 * initializes the data for a new game
 */
void init_game(void)
{
    /*
     * the initial cells of the snake. They are related to the snake initial
     * length and its direction
     */
    const Cell init_snake_body[SNAKE_INIT_LEN] = {
            {GRID_LINES / 2, GRID_COLS / 2},
            {GRID_LINES / 2, (GRID_COLS / 2) - 1},
            {GRID_LINES / 2, (GRID_COLS / 2) - 2},
            {GRID_LINES / 2, (GRID_COLS / 2) - 3},
    };
    int i;

    for (i = 0; i < SNAKE_INIT_LEN; i++) {
        snake[i] = init_snake_body[i];
    }
    snake_length = SNAKE_INIT_LEN;
    direction = RIGHT;
    speed = INIT_SPEED;
    init_obstacles();
    generate_food();
    scoreSnake = 0;
    /*
     * set updated to 1 to allow a first direction change even before the fisrt
     * update
     */
    updated = 1;
    over = 0;
}

Cell *get_obstacles(void)
{
    return obstacles;
}

Cell *get_snake(void)
{
    return snake;
}

int get_snake_length(void)
{
    return snake_length;
}

Cell get_food(void)
{
    return food;
}

int get_score(void)
{
    return scoreSnake;
}

double get_speed(void)
{
    return speed;
}

/*
 * function: update_game
 * ---------------------
 * If the game is not over, moves the snake one step forward, and checks if the
 * snake has eaten the food. If it is the case, increases the length of the
 * snake by one cell, increases the speed, generates a new food, and updates
 * the score. Finally the function checks if the head of the snake is colliding
 * an obstacle. In that case, sets over to 1
 *
 * returns: 1 if the game is over, 0 otherwise
 */
int update_game(void)
{
    Cell tail;
    int i;

    if (!over) {
        /* save the current snake tail */
        tail = snake[snake_length - 1];
        /* move the snake body one step forward */
        for (i = snake_length - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }
        /* move the snake head according to the current direction */
        switch (direction) {
            case LEFT:
                snake[0].x--;
                break;
            case RIGHT:
                snake[0].x++;
                break;
            case UP:
                snake[0].y--;
                break;
            case DOWN:
                snake[0].y++;
                break;
        }
        if (are_equal_cells(snake[0], food)) {
            /*
             * increase the snake length by appending to it, the previously
             * saved tail
             */
            snake[snake_length] = tail;
            snake_length++;
            if (speed - SPEED_CHANGE >= MAX_SPEED) {
                speed -= SPEED_CHANGE;
            }
            generate_food();
            scoreSnake += SCORE_CHANGE;
        }
        if (is_colliding(snake[0], 0)) {
            over = 1;
        }
        updated = 1;
    }
    return over;
}

/*
 * functions: turn_direction
 * -------------------------
 * Change the snake direction to the one corresponding to the called function,
 * only if the current direction is not equal to the new one and it is not its
 * opposite, and an update has occured since the lase direction change
 */
void turn_right(void)
{
    if (updated && (direction == UP || direction == DOWN)) {
        direction = RIGHT;
        updated = 0;
    }
}

void turn_left(void)
{
    if (updated && (direction == UP || direction == DOWN)) {
        direction = LEFT;
        updated = 0;
    }
}

void turn_up(void)
{
    if (updated && (direction == RIGHT || direction == LEFT)) {
        direction = UP;
        updated = 0;
    }
}

void turn_down(void)
{
    if (updated && (direction == RIGHT || direction == LEFT)) {
        direction = DOWN;
        updated = 0;
    }
}
