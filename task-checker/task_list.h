//
// Created by serge on 20.09.2021.
//

#ifndef LINUX_TASK_CHECKER_TASK_LIST_H
#define LINUX_TASK_CHECKER_TASK_LIST_H

#include "tasks/zero/zero.h"
#include "tasks/first/first.h"
#include "tasks/second/second.h"
#include "tasks/third/third.h"
#include "tasks/fourth/fourth.h"
#include "tasks/fifth/fifth.h"
#include "tasks/sixth/sixth.h"
#include "tasks/seventh/seventh.h"
#include "tasks/eighth/eighth.h"
#include "tasks/ninth/ninth.h"

static const char task_list[] = "0 - Hello world\n"
                                "1 - Creating files in directories\n"
                                "2 - Archiving, filtering text, and regular expressions\n"
                                "3 - Access permissions and links\n"
                                "4 - Processes \n"
                                "5 - Bash scripting, information about computer \n"
                                "6 - Bash scripting, positional arguments\n"
                                "7 - Bash scripting, sum arithmetic progression\n"
                                "8 - Bash scripting, greatest common divisor \n"
                                "9 - Packages, ssh, administration \n";

static const struct Task tasks[] = {
        [0] = zero,
        [1] = first,
        [2] = second,
        [3] = third,
        [4] = fourth,
        [5] = fifth,
        [6] = sixth,
        [7] = seventh,
        [8] = eighth,
        [9] = ninth
};
#endif //LINUX_TASK_CHECKER_TASK_LIST_H
