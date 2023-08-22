export HASH_PASS_CODE=($(echo -n "$PASS_CODE" | md5sum  )) && cc -w main.c task_list.h tasks/zero/zero.h \
  tasks/zero/zero.c tasks/task.h \
  tasks/logos/we.h tasks/logos/tux.h \
  integration.c config.h debug_info.h \
  tasks/easter/easter_main.c tasks/easter/easter_main.h \
  tasks/easter/2048.h tasks/easter/2048.c integration.h \
  tasks/easter/cmatrix.c tasks/easter/cmatrix.h \
  tasks/easter/tictactoe.c tasks/easter/tictactoe.h \
  tasks/easter/main_blackjack.c tasks/easter/blackjack.h \
  tasks/easter/blackjack.c tasks/easter/main_blackjack.h \
  tasks/easter/minisweeper.c tasks/easter/minisweeper_def.h \
  tasks/easter/minisweeper_aux.c tasks/easter/minisweeper_menu.c \
  tasks/easter/minisweeper_score.c tasks/easter/minisweeper.h \
  tasks/easter/tetris.h tasks/easter/tetris.c \
  tasks/easter/main_snake.c tasks/easter/snake.c \
  tasks/easter/snake.h tasks/easter/main_snake.h -o "$CHECKERS_PATH"/linux_task_checker \
  -lcurl -lncurses -DUSER_ID_LMS="\"$USER_ID_LMS\"" -DLMS_BASE_URL="\"$LMS_BASE_URL\"" \
  -DLMS_INTEGRATION="1" -DUSER_NAME_LMS="\"$USER_NAME_LMS\"" -DUSER_ID_LMS="\"$USER_ID_LMS\"" \
  -DCOURSE_ID_LMS="\"$COURSE_ID_LMS\"" -DHASH_PASS_CODE="\"$HASH_PASS_CODE\""\
  -DPASS_CODE="\"$PASS_CODE\""
