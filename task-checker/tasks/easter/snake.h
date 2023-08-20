
#ifndef H_SNAKE
#define H_SNAKE
/* snake.h */

/* constants =============================================================== */

#define GRID_LINES 22
#define GRID_COLS 40
#define OBSTACLES_COUNT (GRID_LINES + GRID_COLS) * 2

/* types =================================================================== */

typedef struct cell Cell;

/* structures ============================================================== */

struct cell {
    int y;
    int x;
};

/* entry points ============================================================ */

void init_game(void);
Cell *get_obstacles(void);
Cell *get_snake(void);
int get_snake_length(void);
Cell get_food(void);
double get_speed(void);
int get_score(void);
int update_game(void);
void turn_right(void);
void turn_left(void);
void turn_up(void);
void turn_down(void);

#endif
