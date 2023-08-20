#include <stdio.h>
#include "task_list.h"
#include "tasks/logos/we.h"
#include "tasks/logos/tux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "config.h"
#include "debug_info.h"
#include "tasks/easter/easter_main.h"
#include "integration_openolat.h"

char* execute_command(char* command) {
    FILE *fp;

    /* Open the command for reading. */
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    /* Read the output a line at a time - output it. */
    unsigned int size = 1;  // start with size of 1 to make room for null terminator
    unsigned int strlength;
    char *temp = NULL;
    char *result = NULL;
    char buf[100];
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        strlength = strlen(buf);
        temp = realloc(result, size + strlength);  // allocate room for the buf that gets appended
        if (temp == NULL) {
            printf("Allocation Error\n" );
            exit(1);
        } else {
            result = temp;
        }
        strcpy(result + size - 1, buf);     // append buffer to str
        size += strlength;
    }
    /* close */
    pclose(fp);
    return result;
}

int main() {
    printf("%s", logo_we);
    printf("\n\nHello, %s! Glad to see you now!\n", CONFIG_USER_NAME);
    printf("Please input number of the task being checked\n");
    printf(task_list);
    char num_array[10];
    long num;

    int res = 0;
    while(scanf("%ld", &num) != 1 ) {
        printf("Wrong number format. Please type again\n");
        scanf("%*s");
    }
//    num = strtol(num_array, NULL, 10);
    if (num == DEBUG_NUM) {
        printf("%s", debug_info);
    } else if (num == EAS_NUM) { run_easter(); }
    else {
        if(num < 0 || num >= sizeof(tasks) / sizeof(tasks[0]))
        {
            printf("Wrong number of task \n");
            return 0;
        }
        long i = 0;
        int all_checks = true;
        while (tasks[num].commands[i] != NULL && i < MAX_COMMANDS) {
            char *res = execute_command(tasks[num].commands[i]);
            if (tasks[num].right_answer[i] != NULL &&
                (res == NULL || strcmp(tasks[num].right_answer[i], res) != 0)) {
                printf("Wrong answer, please check your decision. \n");
                printf("Cause: \n");
                printf("%s", tasks[num].prompt[i]);
                all_checks = false;
                break;
            }
            i++;
        }
        if (all_checks == true) {
            char tux_buffer[1000];
            sprintf(tux_buffer, logo_tux, CONFIG_USER_NAME);
            printf("%s", tux_buffer);
            if (strtol(CONFIG_WITH_LMS_CHECKING, NULL, 10) == 1) {
                printf("\nPlease wait, your mark setting on LMS...\n");
                if(setInMarkInLms(tasks[num].task_id, tasks[num].score) == LMS_OK_STATUS) {
                    printf("\nYour mark successfully set on LMS!\n");
                } else {
                    printf("\nSomething went wrong. Your mark is not set on LMS. Please, try again"
                           " or write message to support team \n");
                }
            }
        }
}
    return 0;
}
