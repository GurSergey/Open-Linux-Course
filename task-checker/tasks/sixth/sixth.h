//
// Created by serge on 10.10.2021.
//
#include <stdlib.h>
#include "../task.h"
#include "../../config.h"

#ifndef LINUX_TASK_CHECKER_SIXTH_H
#define LINUX_TASK_CHECKER_SIXTH_H

const struct Task sixth = {
        // commands for checking
        {
            "ls | grep -w 'script.sh'\n", // #1
            "bash script.sh one two \n", // 2
            "bash script.sh 321 123 \n",
            "bash script.sh ten nine \n"
         },
        // right answer
        {
            "script.sh\n", //1
            "Arguments are: $1=one $2=two\n",
            "Arguments are: $1=321 $2=123\n",
            "Arguments are: $1=ten $2=nine\n"
        },
        // prompts for task
        {
            "Not found file script.sh\n",
            "Wrong answer, expected: \"Arguments are: $1=one $2=two\" \n",
            "Wrong answer, test 2 failed\n",
            "Wrong answer, test 3 failed\n"
         },
        // secret strings
        "111",
        //
        CONFIG_SIXTH_TASK_SCORE,
        //
        CONFIG_SIXTH_TASK
};
#endif //LINUX_TASK_CHECKER_SIXTH_H
