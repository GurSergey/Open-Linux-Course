//
// Created by serge on 10.10.2021.
//
#include <stdlib.h>
#include "../task.h"
#include "../../config.h"

#ifndef LINUX_TASK_CHECKER_NINTH_H
#define LINUX_TASK_CHECKER_NINTH_H

const struct Task ninth = {
        // commands for checking
        {
            "ls | grep -w 'hello.jar'\n", // #1
            "java --version > /dev/null ; echo $? \n", // 2
            "java -jar hello.jar | grep -w \"Hello\"  \n", // 3
            "ls | grep -w 'test.txt' \n", // 4
            "cat test.txt | grep -w \"You are almost\" | wc -l\n", // 5
            "ls | grep -w 'image.jpg' \n", // 6
            "md5sum image.jpg | awk '{ print $1 }'", //7
            "ls | grep -w 'secret.txt' \n", // 8
            "echo 'if [[ $(diff <( hostname | md5sum | cut -d\" \" -f1 ) " // №9 on next line continue
            "<(cat secret.txt | xargs)) == \"\" ]] ; then echo \"OK\"; else echo \"-1\"; fi' | bash -s \n",
            "curl --version > /dev/null ; echo $? \n", // 10
            "curl --connect-timeout 4 -s localhost:8082 | grep \"Hello\" | wc -l \n", // 11
            "curl --connect-timeout 4 -s http://localhost:8080/actuator/health | grep UP | wc -l \n" // 12
         },
        // right answer
        {
            "hello.jar\n", //1
            "0\n", // 2
            "Hello!!!\n", // 3
            "test.txt\n", // 4
            "1\n", // 5
            "image.jpg\n", // 6
            "d7e0c29456da3335093da1221f9ebd8f\n", // 7
            "secret.txt\n", // 8
            "OK\n", // 9
            "0\n", // 10
            "1\n", // 11
            "1\n" //12
        },
        // prompts for task
        {
            "Not found file hello.jar\n", // 1
            "Java Machine not found in system. Please, install JDK\n", // 2
            "Something went wrong. Command 'java -jar hello.jar'\n", // 3
            "Not found file test.txt\n", // 4
            "Wrong decision, content of test.txt \n", // 5
            "Not found file image.jpg\n", // 6
            "Wrong decision, content of image.jpg\n", // 7
            "Not found file secret.txt\n", // 8
            "Wrong decision, content of secret.txt\n", // 9
            "Curl not found. Please, install curl\n", // 10
            "Wrong decision, some problems with tunnel on localhost:8082. Please, check this url in web-browse \n", // 11
            "Wrong decision, some problems with web app on localhost:8080. Please, check ssh tunnel for db and/or url in web-browser\n" // 12
         },
        //
        CONFIG_NINTH_TASK
};
#endif //LINUX_TASK_CHECKER_NINTH_H
