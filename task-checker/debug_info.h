//
// Created by serge on 03.10.2021.
//

#include "config.h"

#ifndef LINUX_TASK_CHECKER_DEBUG_INFO_H
#define LINUX_TASK_CHECKER_DEBUG_INFO_H

#define DEBUG_NUM -10

char* debug_info = "This is debug information about task checker \n"
             "Metodhist of Linux course: Alexander Sharabarin \n"
             "Integration with lms developed: Maxim Kozhinov\n"
             "Task checker developed: Sergey Gurylev \n\n"
             "Information build \n"
             "Version of program: 0.5 \n"
             "Lms integration include: " CONFIG_WITH_LMS_CHECKING "\n"
             "User id in LMS: " CONFIG_USER_ID "\n"
             "User name in LMS: " CONFIG_USER_NAME "\n"
               "URL lms: " CONFIG_BASE_URL "\n"
                   "lms login robot: " CONFIG_LOGIN_ROBOT "\n"
                   "lms pass hash: " CONFIG_HASH_PASS_ROBOT "\n"
                   "0 Task id: " CONFIG_ZERO_TASK "\n"
                   "0 Task score: " CONFIG_ZERO_TASK_SCORE "\n"
                   "1 Task id: " CONFIG_FIRST_TASK "\n"
                   "1 Task score: " CONFIG_FIRST_TASK_SCORE "\n"
                   "Id course in LMS: " CONFIG_COURSE_ID "\n\n"
             "About \n"
             "This program developed for automation checking tasks Linux course \n"
             "You can send feedback to emails: gyrsergey@yandex.ru, gyrsergey@gmail.com \n"
             "Or skype login: gyrsergey";

#endif //LINUX_TASK_CHECKER_DEBUG_INFO_H
