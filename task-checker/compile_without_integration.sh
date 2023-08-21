export HASH_PASS_LMS_ROBOT=($(echo -n "$PASS_LMS_ROBOT" | md5sum  )) && cc main.c task_list.h tasks/zero/zero.h \
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
  tasks/easter/snake.h tasks/easter/main_snake.h -o linux_task_checker \
  -lcurl -lncurses -DUSER_ID_LMS="\"$USER_ID_LMS\"" -DLMS_BASE_URL="\"$LMS_BASE_URL\"" \
  -DLMS_INTEGRATION="0" -DUSER_NAME_LMS="\"$USER_NAME_LMS\"" -DUSER_ID_LMS="\"$USER_ID_LMS\"" \
  -DCOURSE_ID_LMS="\"$COURSE_ID_LMS\"" -DHASH_PASS_LMS_ROBOT="\"$HASH_PASS_LMS_ROBOT\""\
  -DPASS_LMS_ROBOT="\"$PASS_LMS_ROBOT\"" \
  -DZERO_TASK_ID="\"$ZERO_TASK_ID\"" \
  -DFIRST_TASK_ID="\"$FIRST_TASK_ID\"" \
  -DSECOND_TASK_ID="\"$SECOND_TASK_ID\"" \
  -DTHIRD_TASK_ID="\"$THIRD_TASK_ID\""  \
  -DFOURTH_TASK_ID="\"$FOURTH_TASK_ID\"" \
  -DFIFTH_TASK_ID="\"$FIFTH_TASK_ID\"" \
  -DSIXTH_TASK_ID="\"$SIXTH_TASK_ID\"" \
  -DSEVENTH_TASK_ID="\"$SEVENTH_TASK_ID\"" \
  -DEIGHTH_TASK_ID="\"$EIGHTH_TASK_ID\"" \
  -DNINTH_TASK_ID="\"$NINTH_TASK_ID\"" \
  -DTENTH_TASK_ID="\"$TENTH_TASK_ID\""
