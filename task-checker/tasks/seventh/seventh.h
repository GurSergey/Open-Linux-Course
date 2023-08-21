//
// Created by serge on 10.10.2021.
//
#include <stdlib.h>
#include "../task.h"
#include "../../config.h"

#ifndef LINUX_TASK_CHECKER_SEVENTH_H
#define LINUX_TASK_CHECKER_SEVENTH_H

const struct Task seventh = {
        // commands for checking
        {
            "ls | grep -w 'script.sh'\n", // #1
            "bash script.sh 1 10 \n", // 2
            "bash script.sh 1 100 \n", // 3
            "bash script.sh 20 30 \n", // 4
            "bash script.sh 100 110 \n", // 5
            "bash script.sh 100 102 \n" // 6
         },
        // right answer
        {
            "script.sh\n", //1
            "55\n", // 2
            "5050\n", // 3
            "275\n", // 4
            "1155\n", // 5
            "303\n" // 6
        },
        // prompts for task
        {
            "Not found file script.sh\n",
            "Wrong answer, parameters 1 and 10 expected: 55 \n",
            "Wrong answer, test 2 failed\n",
            "Wrong answer, test 3 failed\n",
            "Wrong answer, test 4 failed\n",
            "Wrong answer, test 5 failed\n"

         },
        //
        CONFIG_SEVENTH_TASK
};
#endif //LINUX_TASK_CHECKER_SEVENTH_H
