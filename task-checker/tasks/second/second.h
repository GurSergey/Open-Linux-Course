//
// Created by serge on 10.10.2021.
//
#include <stdlib.h>
#include "../task.h"
#include "../../config.h"

#ifndef LINUX_TASK_CHECKER_SECOND_H
#define LINUX_TASK_CHECKER_SECOND_H

const struct Task second = {
        // commands for checking
        {"ls | grep 'hamlet.txt\\|logs\\|hw_200.csv' | sort -f | xargs\n",
         "ls | grep 'to_be.txt\\|lord.txt\\|well.txt\\|mood.txt\\|height.txt\\|renew.txt'| sort -f | xargs\n",
         "echo \"$(cat to_be.txt)\" | head -n 1 | xargs\n",
         "echo \"$(cat lord.txt)\" | head -n 1 | xargs\n",
         "echo \"$(cat mood.txt)\" | head -n 1 | xargs\n",
         "echo \"$(cat height.txt)\" | head -n 1 | xargs\n",
         "echo \"$(cat renew.txt)\" | head -n 1 | xargs\n",
         "ls ./logs1 | sort -f | xargs\n"
         },
        // right answer
        {"hamlet.txt hw_200.csv logs logs1\n",
         "height.txt lord.txt mood.txt renew.txt to_be.txt well.txt\n",
         "Ham\n",
         "177\n",
         "Her mood will needs be pitied\n",
         "69.80\n",
         "684\n",
         "error_log.1 error_log.10 error_log.11 error_log.2 error_log.3 error_log.4 error_log.5 error_log.6 error_log.7 error_log.8 error_log.9\n"
        },
        // prompts for task
        {"Not found file or directory: hamlet.txt, hw_200.csv, logs, logs1\n",
         "Not found file or files with answer: height.txt lord.txt well.txt mood.txt renew.txt to_be.txt \n",
         "Wrong answer in file to_be.txt. Check you decision\n",
         "Wrong answer in file lord.txt. Check you decision\n",
         "Wrong answer in file mood.txt. Check you decision\n",
         "Wrong answer in file height.txt. Check you decision\n",
         "Wrong answer in file renew.txt. Check you decision\n",
         "incorrect contents of the logs1 folder. Check, maybe, you copied unnecessary or did not copy the necessary files\n"
         },
        // secret strings
        "111",
        //
        CONFIG_SECOND_TASK_SCORE,
        //
        CONFIG_SECOND_TASK
};
#endif //LINUX_TASK_CHECKER_SECOND_H
