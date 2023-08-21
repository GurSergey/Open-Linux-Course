//
// Created by serge on 20.09.2021.
//

#define MAX_COMMANDS 1024

#ifndef LINUX_TASK_CHECKER_TASK_H
#define LINUX_TASK_CHECKER_TASK_H

 struct Task
{
    char* commands[MAX_COMMANDS];
    char* right_answer[MAX_COMMANDS];
    char* prompt[MAX_COMMANDS];
    char* task_id;
} ;

#endif //LINUX_TASK_CHECKER_TASK_H
