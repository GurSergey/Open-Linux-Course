//
// Created by serge on 10.10.2021.
//
#include <stdlib.h>
#include "../task.h"
#include "../../config.h"

#ifndef LINUX_TASK_CHECKER_FIRST_H
#define LINUX_TASK_CHECKER_FIRST_H

const struct Task first = {
        // commands for checking
        {"ls -d */ | grep dir1 \n",
         "ls -d dir1/*/ | grep dir2\n",
         "ls -d dir1/*/ | grep dir4\n",
         "ls -p dir1/ | grep -v / | grep file1\n",
         "ls -p dir1/ | grep -v / | grep file2\n",
         "ls -p dir1/dir2 | grep -v / | grep file3\n",
         "ls -p dir1/dir2 | grep -v / | grep file4\n",
         "ls -d dir1/dir2/*/ | grep dir3\n"},
        // right answer
        {"dir1/\n",
         "dir1/dir2/\n",
         "dir1/dir4/\n",
         "file1\n",
         "file2\n",
         "file3\n",
         "file4\n",
         "dir1/dir2/dir3/\n"},
        // prompts for task
        {"Not found directory dir1\n",
         "Not found directory dir2\n",
         "Not found directory dir4\n",
         "Not found file1\n",
         "Not found file2\n",
         "Not found file3\n",
         "Not found file4\n",
        "Not found dir3\n"},
        //
        CONFIG_FIRST_TASK
};
#endif //LINUX_TASK_CHECKER_FIRST_H
