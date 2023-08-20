//
// Created by serge on 20.09.2021.
//

#include <stdlib.h>
#include "../task.h"
#include "../../config.h"


#ifndef LINUX_TASK_CHECKER_ZERO_H
#define LINUX_TASK_CHECKER_ZERO_H

const struct Task zero = {
        // commands for checking
        {"uname\n", "ls | grep 1.txt\n",
         "echo 'res=$(cat 1.txt) ; if [[ $res == *\"Hello world\"* ]] ; "
         "then echo \"OK\"; else echo \"-1\"; fi' | bash -s"},
        // right answer
        {"Linux\n", "1.txt\n", "OK\n"},
        // prompts for task
        {"Your OS is not Linux", "File 1.txt is not found in your folder", "Your file must contain Hello world!" },
        // secret strings
        "111",
        //
        CONFIG_ZERO_TASK_SCORE,
        //
        CONFIG_ZERO_TASK
};
#endif //LINUX_TASK_CHECKER_ZERO_H
