//
// Created by serge on 10.10.2021.
//
#include <stdlib.h>
#include "../task.h"
#include "../../config.h"

#ifndef LINUX_TASK_CHECKER_FOURTH_H
#define LINUX_TASK_CHECKER_FOURTH_H

const struct Task fourth = {
        // commands for checking
        {
            "pgrep -a sleep | cut -f 2,3 -d \" \" | grep \"sleep 36000\"\n", //№1
            "pgrep -a sleep | cut -f 2,3 -d \" \" | grep \"sleep 18000\"\n", //№2
            "ls | grep -w 'vendor.txt'\n", // №3
            "echo 'if [[ $(diff <(cat /proc/cpuinfo | grep \"vendor_id\" | sort | uniq | cut -d \":\" -f2 | xargs ) " // №4 next line continue
            " <(cat vendor.txt | xargs))  == \"\" ]] ; then echo \"OK\"; else echo \"-1\"; fi' | bash -s ",
            "ls | grep -w 'sleep_36000.txt'\n", // №5
            "ls | grep -w 'sleep_18000.txt'\n", // №6
            "echo 'if [[ $(diff <(pgrep -a sleep |  grep \"sleep 36000\" | cut -d \" \" -f1) " // №7 on next line continue
            "<(sed -n 1p sleep_36000.txt)) == \"\" ]] ; then echo \"OK\"; else echo \"-1\"; fi' | bash -s\n",
            "echo 'if [[ $( diff <(cat /proc/$(sed -n 1p sleep_36000.txt)/cmdline | tr -cd \"[:alnum:]._-\" ) " // №8 on next line continue
            "<(sed -n 2p sleep_36000.txt  | tr -cd \"[:alnum:]._-\")) == \"\" ]] ; then echo \"OK\"; else echo \"-1\"; fi ' | bash -s\n",
            "echo 'if [[ $(diff <(pgrep -a sleep |  grep \"sleep 18000\" | cut -d \" \" -f1) " // №9 on next line continue
            "<(sed -n 1p sleep_18000.txt)) == \"\" ]] ; then echo \"OK\"; else echo \"-1\"; fi' | bash -s\n",
            "echo 'if [[ $( diff <(cat /proc/$(sed -n 1p sleep_18000.txt)/cmdline | tr -cd \"[:alnum:]._-\" ) " // №10 on next line continue
            "<(sed -n 2p sleep_18000.txt  | tr -cd \"[:alnum:]._-\")) == \"\" ]] ; then echo \"OK\"; else echo \"-1\"; fi ' | bash -s\n",
            "echo 'if [[ $(diff <(cat /proc/$(sed -n 1p sleep_36000.txt)/status | grep \"State\" | cut -d \":\" -f2 | xargs | " // 11 on next line continue
            "cut -d \" \" -f1) <(sed -n 3p sleep_36000.txt)) == \"\" ]] ; then echo \"OK\"; else echo \"-1\"; fi' | bash -s \n",
            "echo 'if [[ $(diff <(cat /proc/$(sed -n 1p sleep_18000.txt)/status | grep \"State\" | cut -d \":\" -f2 | xargs | " // 12 on next line continue
            "cut -d \" \" -f1) <(sed -n 3p sleep_18000.txt)) == \"\" ]] ; then echo \"OK\"; else echo \"-1\"; fi' | bash -s \n",
            "echo 'if [[ $(diff <(cat /proc/$(ps axo ppid,cmd | grep \"sleep 18000\" | grep -v \"grep\" | xargs | " // 13 on next line continue
            "cut -d\" \" -f1)/status | grep -i ppid | cut -d\":\" -f2 | xargs) <(sed -n 1p parent_id.txt | xargs)) == \"\" ]] ; " // on next line continue
            "then echo \"OK\"; else echo \"-1\"; fi' | bash -s \n",
            "ps ax -o ni,cmd | grep \"sleep 27000\" | sed -n 1p | xargs | cut -d\" \" -f1\n", // 14
            "ps ax -o ni,cmd | grep \"sleep 36000\" | sed -n 1p | xargs | cut -d\" \" -f1\n", // 15
            "ps ax -o ni,cmd | grep \"sleep 18000\" | sed -n 1p | xargs | cut -d\" \" -f1\n" // 16
            },
        // right answer
        {
            "sleep 36000\n", // №1
            "sleep 18000\n", // №2
            "vendor.txt\n", // №3
            "OK\n", // №4
            "sleep_36000.txt\n", // №5
            "sleep_18000.txt\n", // №6
            "OK\n", // №7
            "OK\n", // №8
            "OK\n", // 9
            "OK\n", // 10
            "OK\n", // 11
            "OK\n", // 12
            "OK\n", // 13
            "15\n", //14
            "12\n", // 15
            "12\n" // 16
        },

        // prompts for task
        {
        "Not found process sleep with argument 36000\n", //1
         "Not found process sleep with argument 18000\n", // 2
         "Not found file with name vendor.txt\n", // 3
         "Wrong answer in file vendor.txt\n", // 4
         "Not found file with name sleep_36000.txt\n", //5
         "Not found file with name sleep_18000.txt\n", // 6
         "Wrong answer: PID sleep 36000\n", // 7
         "Wrong answer: cmdline in file sleep_36000.txt\n", //8
         "Wrong answer: PID sleep 18000\n", //9
         "Wrong answer: cmdline in file sleep_18000.txt\n", // 10
         "Wrong answer: status in file sleep_36000.txt\n", // 11
         "Wrong answer: status in file sleep_18000.txt\n", //12
         "Wrong answer: ppid in file parent_id.txt\n", //13
         "Niceness of sleep 27000 not equal 15\n", // 14
         "Niceness of sleep 36000 not equal 12\n", // 15
         "Niceness of sleep 18000 not equal 12\n", // 16
         },
        //
        CONFIG_FOURTH_TASK
};
#endif //LINUX_TASK_CHECKER_FOURTH_H
