cmake_minimum_required(VERSION 3.17)
project(linux_task_checker C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-lcurl)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lcurl -lncurses")
add_executable(linux_task_checker main.c task_list.h tasks/zero/zero.h tasks/zero/zero.c tasks/task.h tasks/logos/we.h
        tasks/logos/tux.h integration.c config.h debug_info.h tasks/easter/easter_main.c
        tasks/easter/easter_main.h tasks/easter/2048.h tasks/easter/2048.c integration.h tasks/easter/cmatrix.c
        tasks/easter/cmatrix.h tasks/easter/tictactoe.c tasks/easter/tictactoe.h tasks/easter/main_blackjack.c
        tasks/easter/blackjack.h tasks/easter/blackjack.c tasks/easter/main_blackjack.h tasks/easter/minisweeper.c
        tasks/easter/minisweeper_def.h tasks/easter/minisweeper_aux.c tasks/easter/minisweeper_menu.c
        tasks/easter/minisweeper_score.c tasks/easter/minisweeper.h tasks/easter/tetris.h tasks/easter/tetris.c
        tasks/easter/main_snake.c tasks/easter/snake.c tasks/easter/snake.h tasks/easter/main_snake.h
        tasks/first/first.h)