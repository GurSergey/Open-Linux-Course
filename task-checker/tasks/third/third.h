//
// Created by serge on 10.10.2021.
//
#include <stdlib.h>
#include "../task.h"
#include "../../config.h"

#ifndef LINUX_TASK_CHECKER_THIRD_H
#define LINUX_TASK_CHECKER_THIRD_H

const struct Task third = {
        // commands for checking
        {
            "ls | grep -w 'summer.txt'\n",
            "ls | grep -w 'slsummer.txt'\n",
            "basename $(readlink -f slsummer.txt)\n",
            "ls | grep -w 'winter.txt'\n",
            "ls | grep -w 'hlwinter.txt'\n",
            "echo 'if [[ $(diff <(ls -li | grep -w winter.txt | tr -s \" \" | cut -d\" \" -f1) <(ls -li | grep -w hlwinter.txt | " //continue test - next line
            "cut -d\" \" -f1)) == \"\" ]] ; then echo \"OK\"; else echo \"-1\"; fi' | bash -s\n",
            "cat /etc/group | grep sports | cut -d':' -f1 \n",
            "cat /etc/group | grep sports | grep $(whoami) | tr -s \" \" | cut -d':' -f1 \n",
            "ls -ld sportsdir/ | tr -s \" \" | cut -d' ' -f4\n",
            "ls | grep -w 'testfile'\n",
            "ls -l | grep testfile  | tr -s \" \" | cut -d' ' -f3\n",
            "ls -l | grep testfile  | tr -s \" \" | cut -d' ' -f4\n",
            "ls -la | grep testfile | tr -s \" \" | cut -d' ' -f1\n",
            "ls -l | grep testdir  | tr -s \" \" | cut -d' ' -f3\n",
            "ls -l | grep testdir  | tr -s \" \" | cut -d' ' -f4\n",
            "ls -la | grep testdir | tr -s \" \" | cut -d' ' -f1"
         },
        // right answer
        {
            "summer.txt\n",
            "slsummer.txt\n",
            "summer.txt\n",
            "winter.txt\n",
            "hlwinter.txt\n",
            "OK\n",
            "sports\n",
            "sports\n",
            "sports\n",
            "testfile\n",
            "new_user\n",
            "new_group\n",
            "-rw-r-x--x\n",
            "new_user\n",
            "new_group\n",
            "drwxr-xr--\n"
        },
        // prompts for task
        {"Not found file summer.txt\n",
         "Not found link slsummer.txt\n",
         "File slsummer.txt is not softlink to summer.txt \n",
         "Not found file winter.txt\n",
         "Not found link hlwinter.txt\n",
         "Files winter.txt and hlwinter.txt have difference inode\n",
         "Not found group with name sports\n",
         "Your user not found in group with name sports\n",
         "Group sports is not owner of directory sportsdir\n",
         "Not found file - testfile\n",
         "User new_user is not owner of file testfile\n",
         "Group new_group is not owner of file testfile\n",
         "Wrong access settings for file testfile. Check your decision \n",
         "User new_user is not owner of directory testdir\n",
         "Group new_group is not owner of directory testdir\n",
         "Wrong access settings for directory testdir. Check your decision \n"
         },
        // secret strings
        "111",
        //
        CONFIG_THIRD_TASK_SCORE,
        //
        CONFIG_THIRD_TASK
};
#endif //LINUX_TASK_CHECKER_THIRD_H
