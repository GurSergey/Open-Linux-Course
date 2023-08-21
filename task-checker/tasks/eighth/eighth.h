//
// Created by serge on 10.10.2021.
//
#include <stdlib.h>
#include "../task.h"
#include "../../config.h"

#ifndef LINUX_TASK_CHECKER_EIGHTH_H
#define LINUX_TASK_CHECKER_EIGHTH_H

const struct Task eighth = {
        // commands for checking
        {
            "ls | grep -w 'script.sh'\n", // #1
            "bash script.sh 10 15 \n", // 2
            "bash script.sh 7 3 \n", // 3
            "bash script.sh 70 30 \n", // 4
            "bash script.sh 169 325 \n", // 5
            "bash script.sh 900 81 \n" // 6
         },
        // right answer
        {
            "script.sh\n", //1
            "GCD is 5\n", // 2
            "GCD is 1\n", // 3
            "GCD is 10\n", // 4
            "GCD is 13\n", // 5
            "GCD is 9\n" // 6
        },
        // prompts for task
        {
            "Not found file script.sh\n",
            "Wrong answer, parameters 10 15 expected: GCD is 5 \n",
            "Wrong answer, test 2 failed\n",
            "Wrong answer, test 3 failed\n",
            "Wrong answer, test 4 failed\n",
            "Wrong answer, test 5 failed\n"

         },
        //
        CONFIG_EIGHTH_TASK
};
#endif //LINUX_TASK_CHECKER_EIGHTH_H
