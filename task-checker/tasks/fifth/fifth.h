//
// Created by serge on 10.10.2021.
//
#include <stdlib.h>
#include "../task.h"
#include "../../config.h"

#ifndef LINUX_TASK_CHECKER_FIFTH_H
#define LINUX_TASK_CHECKER_FIFTH_H

const struct Task fifth = {
        // commands for checking
        {
            "ls | grep -w 'info.sh'\n", // #1
            "echo 'if [[ $(diff <(echo \"Computer name: $(hostname)\") " // №2 next line continue
            " <(bash info.sh | sed -n 1p))  == \"\" ]] ; then echo \"OK\"; else echo \"-1\"; fi' | bash -s ",
            "echo 'if [[ ! -z $(bash info.sh | sed -n 2p | grep -P \"Processor: .* \\([0-9]{1,3}\\.[0-9]{1,3}GHz\\), " // №3 next line continue
            "[0-9]{1,3} cores\") ]] ; then echo \"OK\"; else echo \"-1\"; fi' | bash -s ",
            "echo 'if [[ ! -z $(bash info.sh | sed -n 3p | grep -P \"RAM size: [0-9]{1,5}GB \\([0-9]{1,3}% free\\)\") ]] ; " // №4 next line continue
            "then echo \"OK\"; else echo \"-1\"; fi' | bash -s",
            "echo 'if [[ ! -z $(bash info.sh | sed -n 4p | grep -P \"HDD capacity: [0-9]{1,7}GB \\([0-9]{1,3}% free\\)\") ]] ; " // №5 next line continue
            "then echo \"OK\"; else echo \"-1\"; fi' | bash -s",
            "echo 'if [[ $(diff <(time=$(cat /proc/uptime | cut -d \" \" -f1 | cut -d\".\" -f1) ; " // №6 next line continue
            "echo \"Current uptime: $((time/3600))H $((time/60%60))M\") " // next line continue
            " <(bash info.sh | sed -n 5p))  == \"\" ]] ; then echo \"OK\"; else echo \"-1\"; fi' | bash -s "
         },
        // right answer
        {
            "info.sh\n", //1
            "OK\n", // 2
            "OK\n", // 3
            "OK\n", // 4
            "OK\n", // 5
            "OK\n" // 6
        },
        // prompts for task
        {
            "Not found file info.sh\n",
            "First line of your output has mistakes (hostname). Check decision\n",
            "Second line of your output has mistakes (processor info). Check decision\n",
            "Third line of your output has mistakes (RAM info). Check decision\n",
            "Fourth line of your output has mistakes (Disk info). Check decision\n",
            "Fifth line of your output has mistakes (Uptime info). Check decision\n"
         },
        // secret strings
        "111",
        //
        CONFIG_FIFTH_TASK_SCORE,
        //
        CONFIG_FIFTH_TASK
};
#endif //LINUX_TASK_CHECKER_FIFTH_H
