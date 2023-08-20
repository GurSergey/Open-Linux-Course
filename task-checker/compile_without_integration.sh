export HASH_PASS_LMS_ROBOT=($(echo -n "$PASS_LMS_ROBOT" | md5sum  )) && cc main.c task_list.h tasks/zero/zero.h \
  tasks/zero/zero.c tasks/task.h \
  tasks/logos/we.h tasks/logos/tux.h \
  integration_openolat.c config.h debug_info.h \
  tasks/easter/easter_main.c tasks/easter/easter_main.h \
  tasks/easter/2048.h tasks/easter/2048.c integration_openolat.h \
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
  -DLOGIN_LMS_ROBOT="\"$LOGIN_LMS_ROBOT\"" -DPASS_LMS_ROBOT="\"$PASS_LMS_ROBOT\"" \
  -DZERO_TASK_ID="\"$ZERO_TASK_ID\"" -DZERO_TASK_SCORE="\"$ZERO_TASK_SCORE\"" \
  -DFIRST_TASK_ID="\"$FIRST_TASK_ID\"" -DFIRST_TASK_SCORE="\"$FIRST_TASK_SCORE\"" \
  -DSECOND_TASK_ID="\"$SECOND_TASK_ID\"" -DSECOND_TASK_SCORE="\"$SECOND_TASK_SCORE\"" \
  -DTHIRD_TASK_ID="\"$THIRD_TASK_ID\"" -DTHIRD_TASK_SCORE="\"$THIRD_TASK_SCORE\"" \
  -DFOURTH_TASK_ID="\"$FOURTH_TASK_ID\"" -DFOURTH_TASK_SCORE="\"$FOURTH_TASK_SCORE\"" \
  -DFIFTH_TASK_ID="\"$FIFTH_TASK_ID\"" -DFIFTH_TASK_SCORE="\"$FIFTH_TASK_SCORE\"" \
  -DSIXTH_TASK_ID="\"$SIXTH_TASK_ID\"" -DSIXTH_TASK_SCORE="\"$SIXTH_TASK_SCORE\"" \
  -DSEVENTH_TASK_ID="\"$SEVENTH_TASK_ID\"" -DSEVENTH_TASK_SCORE="\"$SEVENTH_TASK_SCORE\"" \
  -DEIGHTH_TASK_ID="\"$EIGHTH_TASK_ID\"" -DEIGHTH_TASK_SCORE="\"$EIGHTH_TASK_SCORE\"" \
  -DNINTH_TASK_ID="\"$NINTH_TASK_ID\"" -DNINTH_TASK_SCORE="\"$NINTH_TASK_SCORE\"" \
  -DTENTH_TASK_ID="\"$TENTH_TASK_ID\"" -DTENTH_TASK_SCORE="\"$TENTH_TASK_SCORE\""
